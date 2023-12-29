# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  OpenKrauzeEngine_config = debug

else ifeq ($(config),release)
  OpenKrauzeEngine_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := OpenKrauzeEngine

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

OpenKrauzeEngine:
ifneq (,$(OpenKrauzeEngine_config))
	@echo "==== Building OpenKrauzeEngine ($(OpenKrauzeEngine_config)) ===="
	@${MAKE} --no-print-directory -C src -f Makefile config=$(OpenKrauzeEngine_config)
endif

clean:
	@${MAKE} --no-print-directory -C src -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   OpenKrauzeEngine"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"