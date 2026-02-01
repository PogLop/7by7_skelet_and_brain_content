# (c) Amek Efli 2026

ARCHITEKTURA = pd_linux

PD_LIB = pd_outsiders/m77_test.$(ARCHITEKTURA)

PD_LIB_SOURCE = $(wildcard pd_outsiders/*.c)

all: main.o $(PD_LIB)

test:
	echo "$(PD_LIB_SOURCE)"
	echo "$(ARCHITEKTURA)"
	echo "$(PD_LIB)"

main.o: deda.c gridlock_room.c halohalo_buffer.c main.c pnuk_driver.c pnuk.c room.c $(PD_LIB)
	gcc -Wall -o main.o main.c -lpigpio
	sudo chmod +x *.sh
#	sudo ./main.o

$(PD_LIB): $(PD_LIB_SOURCE)
	cd pd_outsiders && $(MAKE) CLASS_FILES=$(notdir $(PD_LIB_SOURCE))

clean:
	rm -f main.o
	rm -f pd_outsiders/*.o
	rm -f pd_outsiders/*.$(ARCHITEKTURA)

# danger zone? asi
synco-me:
	echo "!!!"
	./sync-him-the.dev.sh
	echo "!!!"

synco-him:
	rsync -av --delete . poklop@192.168.1.113:/home/poklop/77/telefonni_centrala_na_rohu_77
