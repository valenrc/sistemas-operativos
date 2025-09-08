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
da un snapshot de *una seleccion* de procesos actuales.
Por defecto selecciona todos los procesos que tengan el mismo USERID que el usuario y que estén "asociados" con la misma terminal que el "invoker". (???)
Para cada proceso muestra su Process ID (PID)

Con el flag -e lista todos los procesos en el sistema. 

## top
Es como el admin. de tareas de windows. 
Es una interfaz que muestra los procesos del sistema manejados por el s.o. en tiempo real
