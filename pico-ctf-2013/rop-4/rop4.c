#include <stdio.h>
#include <unistd.h>
#include <string.h>

char exec_string[20];

void exec_the_string() {
	execlp(exec_string, exec_string, NULL);
}

void call_me_with_cafebabe(int cafebabe) {
	if (cafebabe == 0xcafebabe) {
		strcpy(exec_string, "/sh");
	}
}

void call_me_with_two_args(int deadbeef, int cafebabe) {
	if (cafebabe == 0xcafebabe && deadbeef == 0xdeadbeef) {
		strcpy(exec_string, "/bin");
	}
}

void vulnerable_function() {
	char buf[128];
	read(STDIN_FILENO, buf, 512);
}

void be_nice_to_people() {
	// /bin/sh is usually symlinked to bash, which usually drops privs. Make
	// sure we don't drop privs if we exec bash, (ie if we call system()).
	gid_t gid = getegid();
	setresgid(gid, gid, gid);
}

int main(int argc, char** argv) {
	exec_string[0] = '\0';
	be_nice_to_people();
	vulnerable_function();
}
