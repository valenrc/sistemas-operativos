```man grep```

grep imprime cada linea dentro de un archivo que coincide con un patrón pasado por parámetro. 

ej. ```grep escalera archivo_mist.txt```

| opcion    | descripcion |
| -------- | ------- |
| -n  | imprime el numero de linea  |
| -c  | cuenta el numero de lineas que coinciden   |
| -i  | ignora las mayusculas  |
| -v  | invierte el matching, imprime las lineas que NO coinciden |
| -w  | matchea por palabra entera |

Resultado de `grep -v login /etc/passwd`: 
```
root:x:0:0:root:/root:/bin/bash
sync:x:4:65534:sync:/bin:/bin/sync
vagrant:x:1000:1000:vagrant,,,:/home/vagrant:/bin/bash
memcache:x:102:110:Memcached,,,:/nonexistent:/bin/false
tallerso:x:1001:1001:usuario talleres SO - dc.uba.ar:/home/tallerso:/bin/bash
``` 
