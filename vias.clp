(defrule cruzando
    (declare (salience 1))
    ?s1 <- (Sensor (idcelula 1) (estado activada) (idsemaforo ?idsem))
    ?s2 <- (Sensor (idcelula 2) (estado actuvada) (idsemaforo ?idsem))
    ?v <- (Vehiculo (matricula ?mat) (estado llegando|esperando) (idsemaforo ?idsem))
    ?sem <- (Semaforo (idsemaforo ?idsem) (idvia ?idvia) (numvehiculos ?numveh_sem) (estado Verde))
    ?via <- (Via (idvia ?via1) (nombrevia ?nvia1) (numvehiculos ?nveh_via))
    (Via (idvia ?via2) (nombrevia ?nvia2))
    (test (neq ?via1 ?via2))

    =>

    (bind ?aux1 (+ ?numveh_sem 1))
    (bind ?aux2 (+ ?nveh_via 1))
    (modify ?sem (numvehiculos ?aux1))
    (modify ?via (numvehiculos ?aux2))
    (modify ?s1 (estado desactivada))
    (modify ?s2 (estado desactivada))
    (modify ?v (estado cruzando))
)