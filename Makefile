# (c) Amek Efli 2026 (Já)

ARCHITEKTURA = pd_darwin # for purposes of further development (pd_darwin i mean)

PD_LIB = pd_outsiders/7m7mornings_external.$(ARCHITEKTURA)
PD_LIB_SOURCE = $(wildcard pd_outsiders/*.c)

all: main.o $(PD_LIB)

help:
	@echo "make test"
	@echo "make (all)"
	@echo "make synco-him ADDR=<ip>"
	@echo "make synco-me ADDR=<ip>"

test:
	@echo "$(ARCHITEKTURA)"
	@echo "$(PD_LIB_SOURCE)"
	@echo "$(PD_LIB)"

main.o: deda.c gridlock_room.c halohalo_buffer.c main.c pnuk_driver.c pnuk.c room.c $(PD_LIB)
	gcc -Wall -o main.o main.c -lpigpio
	sudo chmod +x *.sh
#	sudo ./main.o

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
	rsync -av --delete . poklop@$(ADDR):/home/poklop/77/telefonni_centrala_na_rohu_77