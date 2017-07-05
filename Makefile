BUILDDIR = ./build
SRCDIR = $(realpath ./src)
BINDIR = $(BUILDDIR)/bin
OBJDIR = $(BUILDDIR)/obj
CXX = g++
CXXLIBS += -lncurses
CXXFLAGS += -I$(SRCDIR) -std=c++11

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
make-depend-cxx=$(CXX) $(CXXFLAGS) -MM -MF $3 -MP -MT $2 $1

SOURCES = $(SRCDIR)
SRC_CXX = $(call rwildcard,$(SOURCES),*.cpp)
OBJECTS_CXX = $(notdir $(patsubst %.cpp,%.o,$(SRC_CXX)))
TARGET = $(BINDIR)/snake

.PHONY: all clean run

all: $(TARGET)

run: $(TARGET)
	$(TARGET)

ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(OBJECTS_CXX:.o=.d))
endif

$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR)


$(TARGET): $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) -o $@ $(CXXLIBS)

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILDDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) -c -o $@ $<
