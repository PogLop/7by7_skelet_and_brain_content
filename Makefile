synco-me:
	rsync -av --delete poklop@192.168.1.110:/home/poklop/77/telefonni_centrala_na_rohu_77 ..
synco-him:
	rsync -av --delete . poklop@192.168.1.110:/home/poklop/77/telefonni_centrala_na_rohu_77

stuff:
	gcc -Wall -o main.o main.c pnuk.c pnuk_driver.c halohalo_buffer.c room.c deda.c gridlock_room.c -lpigpio
	sudo ./main.o