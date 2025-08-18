## whoami
Da el nombre del usuario asociado con el "userid efectivo" actual
### User identifier
El UID sirve para determinar que recursos del sistema puede acceder determinado usuario.
#### Effective user id
?
#### Real user id
?

## uname
Da informacion del sistema, si no tiene flag, da el nombre del kernel.
La opción -a imprime toda la información del sistema:
- kernel name
- network node hostname
- kernel release
- versión del kernel
- nombre de la computadora
- tipo del procesador (arquitectura)
- hardware platform
- sistema operativo


Ejemplo: "Linux pc67 6.14.0-27-generic #27~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue Jul 22 17:38:49 UTC 2 x86_64 x86_64 x86_64 GNU/Linux"

## id
da los UID de los grupos y usuarios reales y efectivos. Un grupo es un grupo de usuarios. 

## ps
da un snapshot de *algunos* procesos actuales	. Con el flag -e lista todos. 
