# Tema 3 ASC
# ALDICA MARIA MIRUNA, 331CA

Scopul temei este observarea și înțelegerea 
diferențelor dintre timpii de execuție a 3
programe ce au un scop comun: operația pe matrici
**```C = (A.t × B + B × A) × B.t```**, unde
A este o matrice superior triunghilară.

## Explicarea codului pentru fiecare metodă în parte:
### Blas
Pentru mine a fost cea mai grea metodă de implementat,
deoarece site-ul oficial m-a ajutat doar să înțeleg 
ce funcții trebuie să aplic, dar a fost nevoie de
o documentare mai asiduă petru a înțelege exact ce
parametrii trebuie folosiți pentru fiecare funcție în
parte.
Aceasta e de departe cea mai eficientă metodă,
ceea ce poate fi observat cu ochiul liber doar
privind timpii de excuție comparați cu cei de la
celelalte 2 variante.
Pentru implementarea propriu zisă, după ce am citit din
documentație ce face fiecare funcție, am ajuns să ma folosesc
doar de 3, și anume:

1. ```cblas_dtrmm``` - pentru înmulțirile unde aveam ori A ori A.t,
ambele fiind matrice triunghiulare.

2. ```cblas_dgemm``` - pentru înmulțirile clasice de matrice +
pentru că ne permite să specificăm dacă matricele sunt transpuse.

3. ```cblas_dcopy``` - pentru a copia B în AtB și B în BA,
înainte de a face înmuțirile, pentru a evita modificarea matricei
B în operațiile viitoare.

### Neoptimizată
Am folosit algoritmul clasic de înmulțire a matricelor,
având grijă să țin cont că A este superior triunghilară.
Ca mențiuni:

1. Calculul transpuselor a fost realizat după metoda
```At[j * N  + i] = A[i * N + j]```

2. Înmulțirea metricelor a fost realiză după algoritmul:
```C
    for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				BA[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}
```

3. De asemenea, în cazul înmulțirilor unde apare o matrice triunghilară, operația a putut fi simplificată
pentru a reduce numărul de operații necesare,
ținând cont de faptul ca sub sau deasupra diagonalei
principale avem valori de 0, în funcție de caz.
Ca exemplu de înmulțire pentru cazuri de genul,
avem B * A, cu A superior triunghiulară:
```C
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				BA[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}
```

### Optimizată
Din punct de vedere al logicii implementării, varianta
optimizată este complet identică, doar am adăugat
câteva optimizări, cum ar fi:

1. În fiecare buclă for am declarat ***register int i***
în loc de ***int i***.
2. Am detectat constantele din cadrele ciclurilor
interioare și am ținut variabilele în registre.
M-am folosit și de keyword-ul ***register*** pentru a
oferi un hint compilatorului.

## Grafice
Pemtru grafic, am folosit următorii timpi de excuție
pentru fiecare algoritm în parte:

# Varianta blas
1. 400 -> 0.032413 s

2. 600 -> 0.176025 s

3. 800 -> 0.220670 s

4. 1000 -> 0.588446 s

5. 1200 -> 0.710876 s

De departea cea mai eficientă metodă din cele 3.
Timpul de execuție este mult mai mic, fiind astfel
și o metodă mult mai stabilă și potrivită mai ales
când dorim să facem operații pe matrice cu
dimensiuni mari.

# Varianta neoptimizată
1. 400 -> 0.769440 s

2. 600 -> 4.300715 s

3. 800 -> 7.227302 s

4. 1000 -> 20.44082 s

5. 1200 -> 32.224691

Timpul de excuție comparat cu celelalte 2 metode
este semnificativ mai mare, aceasta metodă
nefiind eficientă, mai ales dacă vorbim de matrice 
de dimensiuni mari.

# Varianta optimizată
1. 400 -> 0.339444 s

2. 600 -> 1.196584 s

3. 800 -> 3.047206 s

4. 1000 -> 6.220156 s

5. 1200 -> 8.850394 s

Reprezintă o optimizare a celei de-a doua metode,
fiind clar mai eficientă din punct de vedere al
timpului de execuție. Totuși, pentru dimensiuni 
mari în continuare se confruntă cu creșteri 
semnificative ale timpului de execuție.

Pentru a realiza graficele m-am folosit de
informațiile de la următorul link:
https://www.w3schools.com/python/matplotlib_pyplot.asp

## Cache
Pentru **I refs**, se poate observa cu o mare ușurință 
că soluția blas a folosit cele mai puține referințe
(251,737,562 la număr), pe când cea neoptimizată cele 
mai multe (5,931,359,973). Cu toate acestea, blas
are cele mai multe miss-uri cu o rată de 0.01%,
spre deosebire de celelalte 2 care au un număr infim,
procentual la 0.00%.

La **D refs** se observă din punct de vedere al numărului
de referințe un comportament asemănător, blas având 
cele mai puține (96,502,415), iar varianta neoptimizată
cele mai multe (2,968,118,049), însă diferența nu mai e una
chiar atât de mare. Pe de altă parte, la miss rate blas de 
data aceasta are cel mai mic procent (1.8%), iar varianta
optimizată cel mai mare (13.3%). Varianta neoptimizată
are un miss rate de 3.8%.

La **Branches** varianta blas în continuare are numărul cel mai mic 
de referințe, iar variantele optimizate și neoptimizate au
numere extrem de apropiate. Pe de altă parte, miss rate-ul
pentru blas are valoare cea mai mare (1.6%), pe când celelalte
2 au miss rate-ul egal (0.4%).

## Memorie
Pentru toate cele 3 variante, se observă cu ușurință că nu
am probleme cu memoria.

## Concluzii
Tema aceasta m-a ajutat să-mi fixez noțiunile
generale de optimizare și printre concluziile mele
principale se află următoarele:

- Timpul de execuție va crește proporțional cu
dimensiunea matricei pentru fiecare metodă abordată.

- Fiecare algoritm tinde să urmeze aceeași tendință
de creștere în mare parte.

- De departea cea mai eficientă metodă este blas,
urmată evident de varianta optimizată, iar cea 
neoptimizată este cea mai neeficientă.

- Deoarece blas execută mai multe operații în același
timp pentru I refs are o rată de miss mai mare, dar 
folosește cele mai puține referințe.

- La D refs, la fel ca la I refs, numărul de referințe
la blas este cel mai mic, iar la varinata optimizată
cel mai mare. În schimb, la miss rate procentul 
cel mai mic e blas, urmat de varianta neoptimizată,
iar procentul cel mai mare se regăsește pentru varianta
optimizată.

- La Branches, la blas, deși mai rapidă, are o rată de miss
mai mare.