## Inspeccionar archivos y directorios

### i
`ls /` muestra los archivos y carpetas del directorio / (root).
El directorio root es la base del file system de linux.

### ii
`ls bin`
| opcion | descripcion |
| --- | --- |
| -a  | all: lista . y .. y archivos que empiezan con . |
| -d  | directory: muestra información del directorio y no su contenido |
| -h  | human-readable: da los tamaños con unidades |
| -l  | long listing format: lista el contenido del directorio con mas detalle (permisos, owner, etc) |
| -S  | Sort: ordena los archivos por tamaño |
| -t  | ordena los archivos por tiempo |
| -r  | modifica las opciones que ordenan con el orden inverso |

### iii
`ls -la /etc` imprime el contenido del directorio /etc con "long listing format" e incluyendo los archivos que empiezan con .

