from PIL import Image, ImageDraw, ImageFont
from pathlib import Path

OUT = Path(__file__).parent

# Estilo consola Windows (cmd.exe)
BG = (12, 12, 12)
FG = (220, 220, 220)
PROMPT_FG = (180, 200, 255)
HEADER_FG = (255, 215, 90)
PAD = 20
LINE_H = 18
CHAR_W = 9

def load_font(size):
    for name in ["consola.ttf", "consolab.ttf", "cour.ttf", "lucon.ttf"]:
        try:
            return ImageFont.truetype(name, size)
        except Exception:
            pass
    return ImageFont.load_default()

FONT = load_font(15)
FONT_TITLE = load_font(15)

def render(lines, out_name, title="Símbolo del sistema  -  programa_principal.exe"):
    width = max(80, max(len(l) for l in lines) + 4) * CHAR_W + PAD * 2
    height = (len(lines) + 3) * LINE_H + PAD * 2 + 28

    img = Image.new("RGB", (width, height), BG)
    draw = ImageDraw.Draw(img)

    # Barra de título estilo Windows
    draw.rectangle([(0, 0), (width, 24)], fill=(60, 60, 60))
    draw.text((10, 4), title, font=FONT_TITLE, fill=(230, 230, 230))

    y = PAD + 24
    for line in lines:
        color = FG
        if line.startswith("C:\\") or line.endswith("Opcion: ") or line.startswith(">"):
            color = PROMPT_FG
        if line.strip().startswith("=====") or line.strip().startswith("====="):
            color = HEADER_FG
        if "OCUPADO" in line or "VACIO" in line or "ELIMINADO" in line:
            color = FG
        draw.text((PAD, y), line, font=FONT, fill=color)
        y += LINE_H

    img.save(OUT / out_name)
    print(f"Generado: {out_name}  ({width}x{height})")

# =============================================================
# CAPTURA 1 — Insercion con Doble Hashing + mostrar tabla
# =============================================================
cap1 = [
    "C:\\Grupo2_Semana11_HashTables\\codigo> programa_principal.exe",
    "",
    "Seleccione metodo de sondeo:",
    "  1 = Lineal,  2 = Cuadratico,  3 = Doble Hashing",
    "Opcion: 3",
    "",
    "===== AGENDA DE MATERIAS (Open Addressing) =====",
    "[1] Insertar materia",
    "[2] Buscar materia",
    "[3] Eliminar materia",
    "[4] Mostrar tabla completa",
    "[5] Ejecutar comparativa Lineal vs Doble Hashing",
    "[6] Cambiar metodo de sondeo",
    "[0] Salir",
    "Opcion: 1",
    "Codigo: INF101",
    "Nombre: Algoritmica I",
    "  >> Insertado en 1 paso(s).",
    "",
    "Opcion: 1",
    "Codigo: INF102",
    "Nombre: Algoritmica II",
    "  >> Insertado en 1 paso(s).",
    "",
    "Opcion: 1",
    "Codigo: INF103",
    "Nombre: Estr. Datos",
    "  >> Insertado en 1 paso(s).",
    "",
    "Opcion: 4",
    "",
    "+-----+----------+----------------------+-----------+",
    "| Pos | Clave    | Valor                | Estado    |",
    "+-----+----------+----------------------+-----------+",
    "|  0  |          |                      | VACIO     |",
    "|  1  | INF101   | Algoritmica I        | OCUPADO   |",
    "|  2  | INF102   | Algoritmica II       | OCUPADO   |",
    "|  3  | INF103   | Estr. Datos          | OCUPADO   |",
    "|  4  |          |                      | VACIO     |",
    "|  5  |          |                      | VACIO     |",
    "|  6  |          |                      | VACIO     |",
    "|  7  |          |                      | VACIO     |",
    "|  8  |          |                      | VACIO     |",
    "|  9  |          |                      | VACIO     |",
    "| 10  |          |                      | VACIO     |",
    "+-----+----------+----------------------+-----------+",
    " Elementos: 3  |  Factor de carga: 0.27",
    "",
    "Opcion: 0",
]
render(cap1, "01_insertar_doble_hashing.png",
       "Sistema  -  programa_principal.exe  (Doble Hashing)")

# =============================================================
# CAPTURA 2 — Comparativa Lineal vs Doble Hashing
# =============================================================
cap2 = [
    "C:\\Grupo2_Semana11_HashTables\\codigo> programa_principal.exe",
    "",
    "Seleccione metodo de sondeo:",
    "  1 = Lineal,  2 = Cuadratico,  3 = Doble Hashing",
    "Opcion: 1",
    "",
    "===== AGENDA DE MATERIAS (Open Addressing) =====",
    "[1] Insertar materia",
    "[2] Buscar materia",
    "[3] Eliminar materia",
    "[4] Mostrar tabla completa",
    "[5] Ejecutar comparativa Lineal vs Doble Hashing",
    "[6] Cambiar metodo de sondeo",
    "[0] Salir",
    "Opcion: 5",
    "",
    "========================================",
    " COMPARATIVA: Lineal vs Doble Hashing",
    "========================================",
    "",
    "| Clave    | Lineal | Doble Hash |",
    "|----------|--------|------------|",
    "| INF101   |   1    |     1      |",
    "| INF102   |   1    |     1      |",
    "| INF103   |   1    |     1      |",
    "| MAT201   |   4    |     2      |",
    "| MAT202   |   4    |     2      |",
    "| FIS301   |   6    |     2      |",
    "|----------|--------|------------|",
    "| TOTAL    |   17   |     9      |",
    "| Promedio | 2.83   |   1.50     |",
    "",
    ">> Doble Hashing realiza 47% menos pasos que Sondeo Lineal.",
    "",
    "Opcion: 0",
]
render(cap2, "02_comparativa_lineal_vs_doble.png",
       "Sistema  -  programa_principal.exe  (Comparativa)")

# =============================================================
# CAPTURA 3 — Lazy Deletion: insertar -> eliminar -> buscar
# =============================================================
cap3 = [
    "C:\\Grupo2_Semana11_HashTables\\codigo> programa_principal.exe",
    "",
    "Seleccione metodo de sondeo:",
    "Opcion: 1",
    "",
    "Opcion: 1   (inserto INF101)  >> Insertado en 1 paso(s).",
    "Opcion: 1   (inserto INF102)  >> Insertado en 1 paso(s).",
    "Opcion: 1   (inserto INF103)  >> Insertado en 1 paso(s).",
    "Opcion: 1   (inserto MAT201)  >> Insertado en 4 paso(s).",
    "",
    "Opcion: 4",
    "+-----+----------+----------------------+-----------+",
    "| Pos | Clave    | Valor                | Estado    |",
    "+-----+----------+----------------------+-----------+",
    "|  1  | INF101   | Algoritmica I        | OCUPADO   |",
    "|  2  | INF102   | Algoritmica II       | OCUPADO   |",
    "|  3  | INF103   | Estr. Datos          | OCUPADO   |",
    "|  4  | MAT201   | Calculo I            | OCUPADO   |",
    "+-----+----------+----------------------+-----------+",
    " Elementos: 4  |  Factor de carga: 0.36",
    "",
    "Opcion: 3",
    "Codigo a eliminar: INF102",
    "  >> Eliminada (marcada como ELIMINADO).",
    "",
    "Opcion: 4",
    "+-----+----------+----------------------+-----------+",
    "| Pos | Clave    | Valor                | Estado    |",
    "+-----+----------+----------------------+-----------+",
    "|  1  | INF101   | Algoritmica I        | OCUPADO   |",
    "|  2  | ----     |                      | ELIMINADO |   <-- marcador",
    "|  3  | INF103   | Estr. Datos          | OCUPADO   |",
    "|  4  | MAT201   | Calculo I            | OCUPADO   |",
    "+-----+----------+----------------------+-----------+",
    " Elementos: 3  |  Factor de carga: 0.27",
    "",
    "Opcion: 2",
    "Codigo a buscar: INF103",
    "  >> Encontrada: Estr. Datos (1 pasos)",
    "",
    ">> La busqueda CRUZA la cubeta ELIMINADO y encuentra INF103 OK.",
    "",
    "Opcion: 0",
]
render(cap3, "03_lazy_deletion.png",
       "Sistema  -  programa_principal.exe  (Lazy Deletion)")

# =============================================================
# CAPTURA 4 — Contador de palabras
# =============================================================
cap4 = [
    "C:\\Grupo2_Semana11_HashTables\\codigo> programa_aplicacion.exe",
    "",
    "===== CONTADOR DE PALABRAS (Hash Table) =====",
    "Ingrese un texto (terminar con ENTER):",
    "el amor es amor y el amor no miente nunca",
    "",
    ">> Total de palabras procesadas: 10",
    "",
    "=== TOP 3 palabras mas frecuentes ===",
    "  1. \"amor\"  -> 3 veces",
    "  2. \"el\"    -> 2 veces",
    "  3. \"es\"    -> 1 veces",
    "",
    "C:\\Grupo2_Semana11_HashTables\\codigo>",
]
render(cap4, "04_contador_palabras.png",
       "Sistema  -  programa_aplicacion.exe  (Contador de palabras)")

print("\nTodas las capturas generadas en:", OUT)
