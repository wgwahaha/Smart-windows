obj=main.o EdpKit.o cJSON.o

edit:main.o EdpKit.o cJSON.o
	gcc -o edit main.o EdpKit.o cJSON.o -lm
main.o:EdpKit.h Common.h cJSON.h

EdpKit.o:EdpKit.h Common.h cJSON.h

cJSON.o:EdpKit.h Common.h cJSON.h

.PHONY : clean
clean :
	rm edit $(obj)
