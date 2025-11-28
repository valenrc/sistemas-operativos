## Guia definitiva de drivers

### POSIX API

```C
int driver_init()
```
Se invoca durante la carga del sistema operativo. Usar para inicializar primitivas de sincronización (sem, mutex) y estructuras de datos. Se puede usar kmalloc para asignar memoria dinámica. 

También usar para mapear interrupciones. 

---

```C
int driver_open()                        // kernel
int open(char* path, mode_t mode)        // usuario
```
El usuario llama a open("/dev/driver", mode) donde mode puede ser "w","r","x". 

`open` es la primer operación que hace el driver cuando un usuario lo invoca. No es necesario declarar este método pero hay que hacerlo para notificar al driver del dispositivo y actualizarlo si corresponde.

Devuelve un file descriptor para poder llamar a funciones del driver como write, read, etc.

---

```C
int driver_close()
int close(int fd)
```

el usuario llama a close(fd) para llamar el file descriptor devuelto por open.

Usar para liberar cualquier estructura de datos inicializada con driver_init si es que corresponde.

---

```C
int driver_read(int* data)
int read(int fd, void buf, size_t count)
```
Usado para leer data del dispositivo. Devuelve la cantidad de bytes leídos exitosamente. 

el usuario llama a `read(fd, buf, size)` para leer datos del driver abierto con file descriptor fd. 
`buf` es un puntero que vive en el espacio de usuario y por lo tanto el driver no puede desreferenciar, en cambio tiene que usar la función `copy_to_user` para escribir en el buffer. 

#### copy_to_user
```C
// copy_to_user(user_buffer, kernel_buffer, size)
int copy_to_user(void* to, void* from, size_t n)
```
Se usa en **driver_read**.

Copia n bytes desde la dirección en kernel-space apuntada por `from`, hacia la dirección en user-space apuntada por `to`. 

[**from** (kernel)] ----(copy_to_user)---> [**to** (user)]

---

```C
int driver_write(int* data)
int write(int fd, void buf, size_t count)
```

Usado para enviar datos al driver. Devuelve la cantidad de bytes escritos exitosamente en el driver.

El usuario llama a `write(fd, buf, n)` para escribir datos (maximo n bytes) que están en buf hacia el file descriptor fd. El driver tampoco puede desreferenciar buf, por eso se utiliza `read_from_user` para leer del buffer y luego copiar los datos como corresponda. 

#### copy_from_user
```C
// copy_from_user(kernel_buffer, user_buffer, size) 
copy_from_user(void* to, void* from, size_t n)
```
Se usa en **driver_write**

Copia n bytes desde la dirección en user space apuntada por `from` hacia la dirección en kernel space apuntada por `to`.

[**to** (kernel)] <---(copy_from_user)---- [**from** (user)]

---

```C
int driver_remove()
```

Se llama cuando se descarga el SO.

### Syscalls
```C
void OUT(int IO_address, int data)
```

Escribe `data` en el registro de E/S `IO_address`. 

```C
int IN(int IO_address)
```

Devuelve el valor almacenado en el registro `IO_address`. 

---

#### Interrupciones

```C
int request_irq(int IRQ, void* handler)
``` 

Asocia el procedimiento (rutina de atención) `handler` al número de interrupción IRQ. Devuelve IRQ_ERROR si IRQ ya está asociada a otro handler o 0 si el request fue exitoso. 

```C
int free_irq(int IRQ)
```

Libera la interrupción IRQ del procedimiento asociado. 


## Bibliografía:
[The kernel development community - Character device drivers](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html)

[The kernel development community - I/O access and Interrupts](https://linux-kernel-labs.github.io/refs/heads/master/labs/interrupts.html)

[Linux Device Drivers - Chapter 3: Char Drivers](https://static.lwn.net/images/pdf/LDD3/ch03.pdf)

Prácticas del campus.