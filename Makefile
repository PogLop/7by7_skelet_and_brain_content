main.o: deda.c gridlock_room.c halohalo_buffer.c main.c pnuk_driver.c pnuk.c room.c
	gcc -Wall -o main.o main.c -lpigpio
	sudo chmod +x *.sh
	sudo ./main.o

clean:
	rm -f main.o

synco-me:
	echo "!!!"
	./sync-him-the.dev.sh
	echo "!!!"

synco-him:
	rsync -av --delete . poklop@192.168.1.113:/home/poklop/77/telefonni_centrala_na_rohu_77