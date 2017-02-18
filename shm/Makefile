test=test_shm
cc=gcc
testSrc=comm.c test_shm.c

$(test):$(testSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(test)
