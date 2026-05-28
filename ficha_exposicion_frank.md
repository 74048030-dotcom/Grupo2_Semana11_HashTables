# 🎤 FICHA DE EXPOSICIÓN — FRANK ABEL CHAMBI CONDORI
**Grupo 2 · Hash Tables · Integrante 4 (PARTE 4) · ~4 minutos**

📄 **Documento:** secciones §9 a §14 (busca "PARTE 4" en `Grupo2_investigacion.md`)
🎯 **Presentación:** diapositivas 14 → 19 (busca tu nombre en el footer)

---

## 🟢 FRASE DE INICIO (memorizar)

> *"Gracias [nombre del compañero]. Ahora voy a mostrarles dónde se usan estas hash tables en la vida real."*

---

## 📊 DIAPOSITIVA 14 — Aplicación: Contador de Palabras (~50 seg)
**Documento: §9**

- Programa que recibe un texto y cuenta palabras.
- Ejemplo: *"el amor es amor y el amor no miente nunca"*
- Resultado: **"amor" = 3**, **"el" = 2**, **"es" = 1**.
- Sin hash table sería **lentísimo** (O(n²)); con hash table es **O(n)**.
- Se usa en: **redes sociales, motores de búsqueda, detección de spam**.

---

## 🌐 DIAPOSITIVA 15 — ¿Qué usa la industria? (~1 min)
**Documento: §10**

- **Python dict** → hash table.
- **Java HashMap** → hash table.
- **Redis / Memcached** → cachés del mundo.
- **DNS** → traduce *google.com* a IP, millones de queries/seg.
- **Git** → identifica commits con hash SHA-1.

> 🎯 Cierre: *"Cada vez que hacen `pip install` o `git commit`, están usando esto."*

---

## 🤖 DIAPOSITIVA 16 — Vibe Coding (~50 seg)
**Documento: §13**

- Usamos **Claude (Anthropic)** para programar.
- 3 errores que tuvimos que corregir nosotros:
  1. `h2` devolvía 0 → rompía el doble hashing.
  2. La búsqueda se cortaba en `ELIMINADO` cuando debía seguir.
  3. Tildes corruptas en Dev C++.

> 🎯 **LECCIÓN CLAVE:** *"La IA acelera, pero si no entiendes la teoría, no detectas los bugs."*

---

## ✅ DIAPOSITIVA 17 — Conclusiones (~50 seg)
**Documento: §14**

- Hash table = arreglo + función hash + colisiones = **O(1)**.
- Tamaño **primo**, factor de carga **< 0.7**.
- **Chaining** → dinámico. **Open Addressing** → velocidad.
- **Doble hashing > Cuadrático > Lineal**.
- **Lazy Deletion es OBLIGATORIA** en Open Addressing.
- Python, Java, Redis, DNS, Git — **todos** lo usan.

---

## 🙋 DIAPOSITIVAS 18-19 — Gracias (~15 seg)

> *"Muchas gracias por su atención. ¿Tienen alguna pregunta?"*

- Sonríe. Espera 3 segundos. Mira al público.

---

## 🆘 SI TE PREGUNTAN ALGO DE CÓDIGO QUE NO SEPAS

> *"Esa es una buena pregunta. Si me lo permite, mi compañero [Integrante 3] puede responder mejor esa parte técnica."*

---

## 💡 TIPS RÁPIDOS

| ✅ HACER | ❌ NO HACER |
|---------|------------|
| Mirar al público | Leer la diapositiva |
| Hablar lento y claro | Decir "ehmm", "este…" |
| Usar las manos al señalar | Esconder las manos en bolsillos |
| Respirar 3 veces antes | Hablar rápido por nervios |
| Sonreír al final | Salir corriendo del frente |

---

## 🎯 CHECKLIST 5 MIN ANTES

- [ ] PDF abierto y proyectado en pantalla.
- [ ] Mi parte empieza en diapositiva **14** (Contador de Palabras).
- [ ] Mi parte termina en diapositiva **19** (créditos).
- [ ] En el footer de mi bloque debe aparecer mi nombre.
- [ ] Recuerdo frase de inicio.
- [ ] Recuerdo frase de cierre.
- [ ] Tengo agua a la mano.
- [ ] Celular en silencio.

---

## 📍 ¿DÓNDE BUSCO EN EL DOCUMENTO?

En `Grupo2_investigacion.md`, presiona **Ctrl+F** y busca:
- **"PARTE 4"** → te lleva al inicio de tu bloque (§9).
- **"Chambi Condori"** → te lleva al marcador con tu nombre.

Tu bloque incluye todas las secciones consecutivas: **§9, §10, §11, §12, §13, §14**.

---

*Universidad Continental · Estructura de Datos · Semana 11 · 2026*
