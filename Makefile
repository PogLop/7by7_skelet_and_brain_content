# (c) Amek Efli 2026 (Já)

ARCHITEKTURA = pd_linux
OP_SY = $(shell uname -s 2>/dev/null)

ifeq ($(OP_SY),Linux)
	ARCHITEKTURA = pd_linux
ifeq ($(OP_SY),Darwin)
	ARCHITEKTURA = pd_darwin

#ARCHITEKTURA = pd_linux # for purposes of further development (pd_darwin i mean)

PD_LIB = pd_outsiders/*.$(ARCHITEKTURA)
PD_LIB_SOURCE = $(wildcard pd_outsiders/*.c)

all: clean $(PD_LIB) main.o

help:
	@echo "make test"
	@echo "make (all)"
	@echo "make synco-him ADDR=<ip>"
	@echo "make synco-me ADDR=<ip>"

test:
	@echo "$(ARCHITEKTURA)"
	@echo "$(PD_LIB_SOURCE)"
	@echo "$(PD_LIB)"

main.o:
	gcc -Wall -o main.o main.c -lpigpio -lrt -pthread
	sudo chmod +x *.sh
	sudo ./main.o &

$(PD_LIB): $(PD_LIB_SOURCE)
	cd pd_outsiders && $(MAKE) && $(MAKE) install && $(MAKE) clean 
# 								CLASS_FILES="$(notdir $(PD_LIB_SOURCE))"

clean:
	rm -f main.o
	rm -f pd_outsiders/*.o
	rm -f pd_outsiders/*.$(ARCHITEKTURA)

# danger zone? asi
synco-me:
	echo "!!!"
	./sync-him-the.dev.sh $(ADDR)
	echo "!!!"

synco-him:
	rsync -av --delete . poklop@$(ADDR):/home/poklop/77 --exclude-from=".rsyncignore"

stop:
	@echo "stopping 77 syntheiszesrs byeee :o/"
	sudo kill $(shell jobs -p)