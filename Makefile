PROGRAM:=Leraje

.PHONY: all test clean

SOURCE_DIRS := $(shell find . -type d -not -path "./.*" -print)

CXXFLAGS += $(addprefix -I,$(SOURCE_DIRS)) 
CXXFLAGS += -Wall -Werror -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -fPIC
LDFLAGS  += -lstdc++ -lfastcgi-daemon2 -shared

SRCEXTS = .cpp

SOURCES = $(foreach dir,$(SOURCE_DIRS),$(wildcard $(addprefix $(dir)/*,$(SRCEXTS))))

OBJS = $(addsuffix .o, $(basename $(SOURCES)))

DEPS = $(OBJS:.o=.d)
DEP_OPT = -MM -MP
DEPEND = $(CC) $(DEP_OPT) $(CFLAGS) $(CPPFLAGS)

all: $(PROGRAM)

%.d:%.c
	@$(DEPEND) $< > $@
	@sed -i 's|.*.o:|$*.o:|' $*.d

%.d:%.cc
	@$(DEPEND) $< > $@
	@sed -i 's|.*.o:|$*.o:|' $*.d

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) -o '$@.so' $(LDFLAGS)

ifneq ($(DEPS),)
  sinclude $(DEPS)
endif		

clean:
	rm -f $(PROGRAM).so $(OBJS) $(DEPS)
	