// PCB de un sistema operativo de 16 bits
typedef struct PCB {
  int STAT;     // valores posibles: KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
  int P_ID;     // process id
  int PC;
  int r0;
  int r1;
  int r15;
  int CPU_TIME; // tiempo de ejecución del proceso
} PCB;

// Hace el intercambio de contexto entre dos procesos
// pcb_0 es el proceso a desalojar, pcb_1 el proceso a ejecutar
void Ke_context_switch(PCB* pcb_0, PCB* pcb_1){
  // Guardo el estado en el pcb del proceso actual
  pcb_0 -> r0 .=. R0;
  pcb_0 -> r1 .=. R1;
  pcb_0 -> r15 .=. R15; // Hacerlo con todos los registros

  int tiempo_ejecución = ke_current_user_time();
  pcb_0 -> CPU_TIME += tiempo_ejecución;
  
  pcb_0 -> STAT = KE_READY;

  // Restaurar todo del proceso siguiente
  pcb_1 -> STAT = KE_RUNNING;
  set_current_process(pcb_1 -> P_ID);
  R0 .=. pcb_1 -> r0
  R1 .=. pcb_1 -> r1
  R15 .=. pcb_1 -> r15
  ret(); // reemplaza el pc y desapila el tope de la pila

  // De algun modo cuando el proceso 2 (pcb_1) o algun otro proceso le devuelve la ejecución al proceso 1 (pcb_0) tiene que volver acá
  // Para eso tengo que guardar el PC con el valor de la instruccion siguiente a ret()
  return;
}