# The variable CC will be the compiler to use for C++ builds.
CC=g++


#The Target Binary Program
TARGET      := EEDatabase

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := cpp
INCDIR      := inc
BUILDDIR    := obj_cpp
TARGETDIR   := bin_cpp
DEPEXT      := d
SRCEXT      := cpp
OBJEXT      := o
OBJDIR      := $(BUILDDIR)

# CXXFLAGS will be the options to pass to the compiler.
CXXFLAGS      := -c -Wall -O3 -g -Wno-pointer-to-int-cast

# LDFLAGS will be the options to pass to the linker.
LDFLAGS=

INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)


SOURCES     := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


# Default Make all
all: directories $(TARGET)

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)	
	@mkdir -p $(BUILDDIR)
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)
#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)
#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CXXFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean
