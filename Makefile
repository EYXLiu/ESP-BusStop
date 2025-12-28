SHELL := /bin/bash
PIDFILE := .backend.pid

ifeq ($(strip $(GOTRANSIT_KEY)),)
$(error GOTRANSIT_KEY is not set)
endif

run:
	@echo "starting backend server"
	.venv/bin/python -u backend/main.py & echo $$! > $(PIDFILE)
	@echo "making pio file"
	pio run -e esp32doit-devkit-v1 -v
	@echo "finished"

clean:
	@echo "stopping backend server"
	@if [ -f $(PIDFILE) ]; then \
		kill $$(cat $(PIDFILE)) && rm -f $(PIDFILE); \
	fi
