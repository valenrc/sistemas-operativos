Procesos P0, P1, P2

- P0 tiene rafagas cortas de E/S a ciertos dispositivos
- P1 se bloquea constantemente leyendo de la red
- P2 tiene rafagas prolongadas de alto consumo de CPU y luego de escritura a disco

Convendría usar política con prioridades donde P0 tenga la mayor prioridad y P2 tenga la menor prioridad, de esa manera aprovecho el poco tiempo de uso de CPU que tiene P0 durante las rafagas de E/S, el cual si P2 tuviera igual o mas prioridad, P0 podría quedarse esperando por un turno cuando realmente podría ejecutarse.

