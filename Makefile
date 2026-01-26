skvrz.out: deda.c gridlock_room.c halohalo_buffer.c main.c pnuk_driver.c pnuk.c room.c
	gcc main.c -o skvrz.out -lpigpio

clean:
	rm -f skvrz.out