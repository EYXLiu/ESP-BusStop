SHELL := /bin/bash
PIDFILE := .backend.pid
LOGFILE := .backend.log

ifeq ($(strip $(MAC_IP)),)
$(error MAC_IP is not set)
endif

all: run

run:
	@echo "starting backend server"
	.venv/bin/python -u backend/main.py >> $(LOGFILE) 2>&1 & echo $$! > $(PIDFILE)
	@echo "making pio file"
	pio run -e esp32doit-devkit-v1 -v
	@echo "finished"

clean:
	@echo "stopping backend server"
	@if [ -f $(PIDFILE) ]; then \
		kill $$(cat $(PIDFILE)) 2>/dev/null || true; \
	fi
	@rm -f $(PIDFILE)
	@rm -f $(LOGFILE)

.PHONY: all run clean
