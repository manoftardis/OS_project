# OS_project
Repository per il progetto di sistemi operativi

## Descrizione
Questa pseudo malloc si occupa di allocare o deallocare memoria tramite due metodi.
Il primo metodo è tramite una bitmap con cui viene gestita l'albero binario della memoria disponibile, questo metodo è usato se la richiesta della grandezza della memoria è minore di 1/4 della grandezza della pagina. L'albero gestito dalla bitmap ha un indice base uguale ad 1 per semplificare i calcoli degli indici del genitore e del buddy. Il secondo metodo che è invocato quando una si esegua una richiesta di memoria uguale o maggiore ad 1/4 della grandezza della pagina è eseguito tramite una mmap che richiede al sistema della memoria della grandezza richiesta. Per quanto riguarda la deallocazione anche essa è eseguita in due modi differenti seguendo le stesse condizioni dell'allocazione. La deallocazione tramite bitmap è eseguita con una funzione apposita che si occupa di liberare il relativo indice nella bitmap. Mentre la deallocazione per memoria maggiore o uguale ad un 1/4 della page size è eseguita tramite munmap.

## Test
Per eseguire il codice basta clonare la repository e compilare il programma.
```
$ git clone https://github.com/manoftardis/OS_project.git
$ cd /OS_project
$ make
```
Si possono eseguire due programmi
### Driver
```
$.\driver
```
Questo programma alloca memoria in tutti e due i modi e poi si occupa di deallocarla

### Buddy_allocator_test
```
$.\buddy_allocator_test
```
Questo programma è utilizzato per testare l'allocatore gestito da bitmap, alloca memoria di varia grandezza e in fine si occupa di deallocarla.

