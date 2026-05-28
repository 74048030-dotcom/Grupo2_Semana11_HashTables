---
marp: true
theme: default
paginate: true
header: "Estructura de Datos — Semana 11 | Universidad Continental | Sección Viernes"
footer: "Grupo 2 — Hash Tables (Open Addressing) | 2026"
style: |
  section {
    font-family: 'Segoe UI', Arial, sans-serif;
    background-color: #F5F3F8;
    color: #1A0A2E;
    font-size: 22px;
  }
  section.portada {
    background-color: #1A0A2E;
    color: white;
    justify-content: center;
    text-align: center;
  }
  section.portada h1 {
    color: #A855F7;
    font-size: 2em;
  }
  section.portada h2 {
    color: #D4B8F0;
    font-size: 1.2em;
    font-weight: normal;
  }
  section.portada p {
    color: #B0A0D0;
    font-size: 0.9em;
  }
  h1 {
    color: #7B2D8B;
    border-left: 8px solid #7B2D8B;
    padding-left: 16px;
    font-size: 1.4em;
  }
  h2 {
    color: #4A1A6B;
    font-size: 1.15em;
  }
  h3 {
    color: #5C2A80;
    font-size: 1em;
  }
  code {
    background-color: #0D1117;
    color: #58A6FF;
    font-family: 'Courier New', monospace;
    border-radius: 4px;
    padding: 2px 6px;
  }
  pre {
    background-color: #0D1117;
    color: #58A6FF;
    font-family: 'Courier New', monospace;
    font-size: 0.75em;
    border-radius: 8px;
    padding: 16px;
    border-left: 4px solid #7B2D8B;
  }
  table {
    font-size: 0.85em;
    border-collapse: collapse;
    width: 100%;
  }
  th {
    background-color: #7B2D8B;
    color: white;
    padding: 8px 12px;
    text-align: center;
  }
  td {
    border: 1px solid #D0B8E0;
    padding: 6px 10px;
  }
  tr:nth-child(even) { background-color: #EDE8F5; }
  blockquote {
    border-left: 4px solid #A855F7;
    background-color: #EDE8F5;
    padding: 10px 16px;
    font-style: italic;
    color: #4A1A6B;
    border-radius: 0 8px 8px 0;
  }
  ul { list-style: none; padding-left: 0; }
  ul li::before { content: "▶ "; color: #7B2D8B; font-size: 0.8em; }
  li { margin-bottom: 6px; }
---

<!-- _class: portada -->

# TABLAS DE DISPERSIÓN
## Hash Tables — Direccionamiento Abierto y Aplicaciones

### Estructura de Datos — Semana 11

**Grupo 2** — Integrante 1, Integrante 2, Integrante 3, Integrante 4

Universidad Continental | Ingeniería de Sistemas e Informática | 2026

---

# ¿Qué aprendió el Grupo 1?

**Resumen rápido (2 min):**
- Hash table = arreglo + función hash → O(1)
- Factor de carga α = n/m → mantener < 0.7
- Chaining: lista enlazada en cada bucket

**Hoy el Grupo 2 cubre:**
- Otra forma de manejar colisiones → **Open Addressing**
- Tres estrategias de sondeo
- Aplicación real: contador de palabras
- ¿Qué usa Python, Java, Redis?

---

# Open Addressing — La Idea

**Sin listas enlazadas.** Todo dentro del arreglo.

Cuando hay colisión → busco el **siguiente bucket disponible** (sondeo).

```
α debe ser SIEMPRE < 1
(más elementos que cubetas = imposible)
```

**Tres estrategias de sondeo:**
1. Sondeo Lineal
2. Sondeo Cuadrático
3. Doble Hashing ← el mejor

---

# Sondeo Lineal

```
h(k, i) = (h'(k) + i) mod m,   con i = 0, 1, 2, ...
```

Si el bucket está ocupado → prueba el siguiente consecutivo.

```
[0]   [1]   [2]Ana  [3]Luis  [4]Pedro  [5]   [6]
              ←──── clustering primario ────→
```

**Problema:** Clustering Primario → cadenas largas → rendimiento cae.

> Analogía: el tráfico en una autopista — si un carril se llena, los autos se apilan.

---

# Sondeo Cuadrático y Doble Hashing

**Sondeo Cuadrático:**
```
h(k, i) = (h'(k) + i²) mod m
Pasos: +1, +4, +9, +16, ...
```
Reduce clustering primario, pero genera clustering secundario.

**Doble Hashing (el mejor):**
```
h(k, i) = (h1(k) + i × h2(k)) mod m
h2(k) = 1 + (hashCode(k) % (m-1))   ← nunca 0
```
El paso depende de la clave → distribución casi perfecta.

---

# Lazy Deletion — Eliminación Inteligente

**El problema:** si borramos un elemento, dejamos un hueco que interrumpe búsquedas.

```
Buscar "Carlos":
[2] OCUPADO ("Ana")   → no es Carlos, sigo
[3] VACÍO              → STOP, no existe (¡pero Carlos sí está en [4]!)
```

**La solución:** marcar como ELIMINADO, no limpiar.

```cpp
enum Estado { VACIO, OCUPADO, ELIMINADO };
// Las búsquedas continúan pasando por ELIMINADO
// Las inserciones pueden reutilizar ELIMINADO
```

---

# Estructura en C++ (sin STL)

```cpp
enum Estado { VACIO, OCUPADO, ELIMINADO };

struct Entrada {
    string clave;
    string valor;
    Estado estado;
};

struct TablaHash {
    int tamanio;
    int numElementos;
    Entrada* tabla;

    int h1(string clave);   // hash primario - djb2
    int h2(string clave);   // hash secundario (≠ 0)
    int sondear(string clave, int i, int metodo);
    int insertar(string clave, string valor, int metodo);
    string buscar(string clave, int metodo, int& pasos);
    bool eliminar(string clave, int metodo);
};
```

---

# Demo — Inserción con Doble Hashing

![h:500](https://raw.githubusercontent.com/74048030-dotcom/Grupo2_Semana11_HashTables/main/capturas/01_insertar_doble_hashing.png)

Insertamos INF101, INF102, INF103 → todos en 1 paso.

---

# Comparativa — Mismo dato, dos métodos

| Clave    | Sondeo Lineal | Doble Hashing |
|----------|---------------|---------------|
| INF101   | 1 paso        | 1 paso        |
| INF102   | 1 paso        | 1 paso        |
| INF103   | 1 paso        | 1 paso        |
| MAT201   | 4 pasos       | 2 pasos       |
| MAT202   | 4 pasos       | 2 pasos       |
| FIS301   | 6 pasos       | 2 pasos       |
| **TOTAL** | **17 pasos** | **9 pasos**   |
| **Promedio** | **2.83**  | **1.50**      |

> Doble hashing: **47 % menos pasos** que sondeo lineal.

---

# Evidencia — Comparativa en consola

![h:550](https://raw.githubusercontent.com/74048030-dotcom/Grupo2_Semana11_HashTables/main/capturas/02_comparativa_lineal_vs_doble.png)

---

# Demo — Lazy Deletion en vivo

![h:550](https://raw.githubusercontent.com/74048030-dotcom/Grupo2_Semana11_HashTables/main/capturas/03_lazy_deletion.png)

> Eliminamos INF102 → INF103 sigue encontrándose porque la búsqueda **cruza** la cubeta marcada como `ELIMINADO`.

---

# Complejidad — Open Addressing

| Operación | Promedio (α < 1) | Peor caso |
|-----------|------------------|-----------|
| Inserción | O(1/(1−α)) | O(n) |
| Búsqueda exitosa | O((1/α) · ln(1/(1−α))) | O(n) |
| Búsqueda fallida | O(1/(1−α)) | O(n) |
| Eliminación (lazy) | O(1/(1−α)) | O(n) |

**Interpretación práctica:**
- α = 0.5 → ≈ 2 pasos por operación
- α = 0.7 → ≈ 3.3 pasos
- α = 0.9 → ≈ 10 pasos ⚠

---

# Chaining vs Open Addressing

| Aspecto | Chaining | Open Addressing |
|---------|----------|-----------------|
| Memoria | Extra (punteros) | Solo arreglo |
| Factor de carga | Puede ser > 1 | Debe ser < 1 |
| Caché CPU | Pobre | Bueno |
| Implementación | Sencilla | Compleja (lazy del.) |
| Hash mediocre | Tolerante | Sensible |

**¿Cuándo cada uno?** Chaining → cantidad muy dinámica. Open Addressing → rendimiento crítico y memoria limitada.

---

# Aplicación — Contador de Palabras

![h:380](https://raw.githubusercontent.com/74048030-dotcom/Grupo2_Semana11_HashTables/main/capturas/04_contador_palabras.png)

**¿Dónde se usa esto?** Análisis de sentimientos · Motores de búsqueda · Detección de spam

---

# ¿Qué usa la industria?

| Sistema | Técnica | Por qué |
|---------|---------|---------|
| **Python dict** | Open Addressing (cuadrático perturbado) | Rápido, RAM compacta |
| **Java HashMap** | Chaining (árbol al saturar) | Seguro en cualquier α |
| **C++ unordered_map** | Chaining | Estándar |
| **Redis** | Hash con rehashing incremental | Caché distribuida |
| **DNS** | Hash distribuida | Millones de queries/seg |
| **Git** | Hash SHA-1 | Identidad de commits |

---

# Vibe Coding — Lo que usamos

**Herramienta:** Claude (Anthropic)

**Prompt:**
> *"Escribe en C++ (sin STL, compatible con Dev C++) una tabla hash con direccionamiento abierto: 3 métodos de sondeo, lazy deletion, menú interactivo, comparativa que cuente pasos."*

**Errores que detectamos:**
- `h2(k)` retornaba 0 → corregimos a `1 + (hashCode % (m-1))`
- La búsqueda se cortaba en ELIMINADO → corregimos: solo VACIO corta
- Caracteres acentuados en consola Windows → reemplazamos por ASCII

**Reflexión:** La IA acelera el esqueleto, pero solo si entiendes la teoría detectas los bugs sutiles.

---

# Conclusiones

**Hash Tables en una frase:**
> Arreglo + función hash + manejo de colisiones = O(1) para todo.

**Recuerda:**
- Tabla de tamaño **primo**.
- α < 0.7 o redimensiona.
- Chaining para cargas altas; Open Addressing para velocidad y caché.
- **Doble hashing > Cuadrático > Lineal** en distribución.
- Lazy Deletion es OBLIGATORIA en Open Addressing.

**En la industria:** Python, Java, Redis, DNS, Git — todos usan hash tables.

---

# Gracias

*¿Preguntas?*

---

**Grupo 2** — Integrantes: [nombres]

**Código disponible en:** `Grupo2_Semana11_HashTables/codigo/`

**Herramienta de IA usada:** Claude (Anthropic)
