.PHONY: all clean check test analyze echo

all:
	$(MAKE) -C ./src
clean:
	rm -rf ./build-files
	rm -rf ./tmp-files
	$(MAKE) -C ./tests clean
	$(MAKE) -C ./src clean
check: analyze echo test
test:
	$(MAKE) -C ./tests
analyze:
	@cppcheck --enable=all --suppress=missingIncludeSystem .
echo: # For printing empty line
	@echo