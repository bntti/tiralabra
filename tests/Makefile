SRCDIR := ..
OBJDIR := ../build-files/tests/obj
DEPDIR := ../build-files/tests/dep
TARGET := test

SRCS := $(shell find $(SRCDIR) -name "*.cpp" | grep -v main.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
TREE := $(patsubst %/,%,$(dir $(OBJS)))
TREE := $(sort $(TREE))
CPPFLAGS = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
CXXFLAGS := -O0 -march=native -Wall -Wextra -Wshadow -fsanitize=undefined -std=c++11 -I /usr/include/catch2/ -fprofile-arcs -ftest-coverage

.PHONY: all clean

all: $(TARGET)
	@echo
	@./$(TARGET)

clean:
	rm -rf $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEPS)
endif
