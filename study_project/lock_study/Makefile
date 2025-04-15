CC := gcc

mutex_test: mutex_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test: rwlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_hungry_solved: rwlock_hungry_solved.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

condition_var: condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_bin_thread: unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_biunnamed_sem_bin_process_conditionn_thread: unnamed_sem_bin_process_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_thread: unnamed_sem_count_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_process: unnamed_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

named_sem_no_unlink: named_sem_no_unlink.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

thread_pool_test: thread_pool_test.c
	-$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`
	-./$@
	-rm ./$@


