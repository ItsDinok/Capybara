CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
LDFLAGS  :=

TARGET   := capybara
BUILDDIR := build

SOURCES  := $(wildcard source/*.cpp)
OBJECTS  := $(patsubst source/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
DEPS     := $(OBJECTS:.o=.d)

.PHONY: all clean debug release

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: source/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

debug: CXXFLAGS += -g -O0
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	rm -rf $(BUILDDIR) $(TARGET)

-include $(DEPS)
