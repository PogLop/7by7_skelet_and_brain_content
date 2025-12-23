vedouci: main.c
	sudo killall pigpiod
	gcc -Wall -pthread -o main.out main.c -lpigpio -lrt
	sudo ./main.out

pnuk: pnuk.c
	sudo killall pigpiod
	gcc -Wall -pthread -o pnuk_test.out pnuk_test.c -lpigpio -lrt
	sudo ./pnuk_test.out

synco-me:
	rsync -av --delete poklop@192.168.1.110:/home/poklop/77/telefonni_centrala_na_rohu_77 ..
synco-him:
	rsync -av --delete . poklop@192.168.1.110:/home/poklop/77/telefonni_centrala_na_rohu_77