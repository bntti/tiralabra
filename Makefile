all:
	$(MAKE) -C ./src
clean:
	rm -rf ./build-files
	rm -rf ./tmp-files
	$(MAKE) -C ./tests clean
	$(MAKE) -C ./src clean
test:
	$(MAKE) -C ./tests