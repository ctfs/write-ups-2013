[snip]

void handle(int newsock) {
	int backdoor = 0;
	char buffer[1016];
	memset(buffer, 0, 1016);

	send(newsock, "Welcome to CSAW CTF.", 21, 0);
	recv(newsock, buffer, 1020, 0);
	buffer[1015] = 0;

	if ( backdoor ) {
		fd = fopen("./key", "r");
		fscanf(fd, "%s\n", buffer);
		send(newsock, buffer, 512, 0);
	}
	close(newsock);
}

[snip]