(defglobal ?*ANNO* = 2022)
(defglobal ?*LIMITEBANCO* = 900)

(deftemplate Usuario
    (slot DNI)
    (slot Pin)
    (slot Dinero (type INTEGER) (default 0))
)

(deftemplate Tarjeta
    (slot Pin)
    (slot DNI)
    (slot Intentos (default 3))
    (slot Limite (default 1000))
    (slot Annocad (default 2023))
    (slot Validada (allowed-values SI NO) (default NO))
)

(deftemplate Cuenta
    (slot DNI)
    (slot Saldo)
    (slot estado (allowed-values enPantalla dineroEntregado Inicial SuperaLimite SinSaldo)
                 (default Inicial))
)

;DEFFACTS
(deffacts Iniciales
    (Tarjeta (DNI 123456) (Pin 1212) (Intentos 3) (Limite 500) (Annocad 2026))
    (Tarjeta (DNI 456456) (Pin 4545) (Intentos 3) (Limite 500) (Annocad 2026))
    (Tarjeta (DNI 000111) (Pin 0011) (Intentos 0) (Limite 500) (Annocad 2026))
    (Cuenta (DNI 123456) (Saldo 5000))
    (Cuenta (DNI 456456) (Saldo 33))
    (Cuenta (DNI 000111) (Saldo 30000))
    (Usuario (DNI 123456) (Pin 1212) (Dinero 300))
)

;FUNCIONES
(deffunction DECREMENTA (?val)
    (return (- ?val 1))
)


;REGLAS VALIDACIÓN DE TARJETA
(defrule Supera_Intentos
    (Tarjeta(Intentos ?intentos))
    (test (eq ?intentos 0))
    =>
    (printout t "Se ha superado el numero de intentos")
)

(defrule Pin_Invalido
    ?tarj <- (Tarjeta (DNI ?dni) (Pin ?pint) (Intentos ?tries))
    ?user <- (Usuario (DNI ?dni) (Pin ?pinu))
    (test (neq ?pint ?pinu))
    =>
    (printout t "El pin es incorrecto")
    (retract ?user)
    (modify ?tarj (Intentos (DECREMENTA ?tries)))
)

(defrule Valida_Tarjeta
    ?tarj <- (Tarjeta (DNI ?dni) (Pin ?pin) (Intentos ?tries) (Annocad ?cad) (Validada NO))
    (test (> ?tries 0))
    (Usuario (DNI ?dni) (Pin ?pin))
    (test (<= ?*ANNO* ?cad))
    =>
    (modify ?tarj (Validada SI))
    (printout t "Se valido una tarjeta")
)