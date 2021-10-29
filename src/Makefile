SRCDIR := .
OBJDIR := ../build-files/src/obj
DEPDIR := ../build-files/src/dep
TARGET := ../bnzip

SRCS := $(shell find $(SRCDIR) -name "*.cpp")
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
TREE := $(patsubst %/,%,$(dir $(OBJS)))
TREE := $(sort $(TREE))
CPPFLAGS = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

BUILD := default
cxxflags.common := -Wall -Wextra -Wshadow
cxxflags.default := -O3 -march=native
cxxflags.release := -O2 -static
CXXFLAGS := ${cxxflags.${BUILD}} ${cxxflags.common}

.PHONY: all clean

all: $(TARGET)

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
