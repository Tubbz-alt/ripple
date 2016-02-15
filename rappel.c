#include <signal.h>
#include <unistd.h>

#include <sys/wait.h>

#include "common.h"
#include "exedir.h"
#include "pipe.h"
#include "ui.h"

// Defaults
struct options_t options = {
	.start = 0x400000,
	.verbose = 0,
	.raw = 0,
	.allregs = 0,
	.savefile = NULL,
};

static
void usage(
		const char *argv0)
{
	fprintf(stderr, "Usage: %s [options]\n"
			"\t-h\t\tDisplay this help\n"
			"\t-r\t\tTreat stdin as raw bytecode (useful for ascii shellcode)\n"
			"\t-s <filename>\tSave generated exe to <filename>\n"
			"\t-x\t\tDisplay all registers (FP)\n"
			"\t-v\t\tIncrease verbosity\n"
			, argv0);

	exit(EXIT_FAILURE);
}

static
void parse_opts(
		int argc,
		char **argv) {
	int c;

	while ((c = getopt(argc, argv, "s:hrvx")) != -1)
		switch (c) {
			case 'h':
				usage(argv[0]);
				break;
			case 'r':
				++options.raw;
				break;
			case 's':
				options.savefile = optarg;
				break;
			case 'v':
				++options.verbose;
				break;
			case 'x':
				++options.allregs;
				break;
			default:
				exit(EXIT_FAILURE);
		}
}

static
void sigchld_handler(int signum, siginfo_t *si, void *uctx)
{
	if (WIFSIGNALED(si->si_status))
		verbose_printf("Process %d has exited on signal %d\n", si->si_pid, WTERMSIG(si->si_status));
	else
		verbose_printf("Process %d has exited with status %d\n", si->si_pid, WEXITSTATUS(si->si_status));
}

int main(int argc, char **argv) {
	// Lot of arg parsing here

	clean_exedir();

	parse_opts(argc, argv);

	struct sigaction sa = {};

	REQUIRE (sigemptyset(&sa.sa_mask) == 0);
	sa.sa_sigaction = sigchld_handler;
	sa.sa_flags     = SA_NOCLDSTOP | SA_SIGINFO;

	REQUIRE (sigaction(SIGCHLD, &sa, NULL) == 0);

	if (isatty(STDIN_FILENO))
		interact(argv[0]);
	else
		pipe_mode();

	return 0;
}