.PHONY: single_conn single_conn_clean

single_conn_executables:=single_conn_server single_conn_client

inet_endian_convert: inet_endian_convert.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


single_conn_server: single_conn_server.c
	-$(CC) -o $@ $^

single_conn_client: single_conn_client.c
	-$(CC) -o $@ $^

single_conn: $(single_conn_executables)

single_conn_clean:
	-rm ./$(word 1, $(single_conn_executables)) ./$(word 2, $(single_conn_executables))

multi_conn_processes_server: multi_conn_processes_server.c
	-$(CC) -o $@ $^

multi_conn_processes_client: multi_conn_processes_client.c
	-$(CC) -o $@ $^

udp_server: udp_server.c
	-$(CC) -o $@ $^

udp_client: udp_client.c
	-$(CC) -o $@ $^

