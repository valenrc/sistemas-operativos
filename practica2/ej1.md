### **Rafagas de CPU**
Son los intervalos de tiempo en donde el proceso está usando activamente la CPU. Durante este tiempo, el proceso está solo consumiendo ciclos de CPU. 

### **Ráfagas de E/S**
Son los intervalos en donde el proceso no puede ejecutarse en CPU por estar esperando a que se complete una operación de E/S. Como leer archivos, escribir en pantalla, recibir datos de red. El proceso se BLOQUEA y la CPU puede ejecutar otro proceso. 

a) identificar rafagas de CPU y E/S
| Tiempo | Evento          |        |
|--------|-----------------|--------|
| 0      | load store      | CPU B  |
| 1      | add store       |        |
| 2      | read de archivo | E/S B  |
| 3      | espera E/S      |        |
| ..     | ..              |        |
| 10     | espera E/S      |        |
| 11     | store increment | CPU B  |
| 12     | inc             |        |
| 13     | write en archivo| E/S B  |
| 14     | espera E/S      |        |
| ..     | ..              |        |
| 20     | espera E/S      |        |
| 21     | load store      | CPU B  |
| 22     | add store       |        |

b)
Duraciones:
CPU burst (2) -> E/S Burst (9) -> CPU Burst (2) -> E/S BURST (8) -> CPU Burst (2)