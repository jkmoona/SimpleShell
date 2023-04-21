
all: myshell writef execx

myshell: myshell.c 
	gcc myshell.c -o myshell 

writef: writef.c 
	gcc writef.c -o writef 

execx: execx.c 
	gcc execx.c -o execx 

clean:
	rm myshell writef execx