#Sin simulacion de sobrecarga de constructores
MAX_ESTUDIANTES = 30
NUM_NOTAS = 3

# =============================================
#  CLASE Estudiante
# =============================================
class Estudiante:

    # Constructor único con valores por defecto
    def __init__(self, codigo=0, nombre="", edad=0, activo=False):
        self.__codigo = codigo
        self.__nombre = nombre
        self.__edad = edad
        self.__activo = activo

    # Getters
    def get_codigo(self):
        return self.__codigo

    def get_nombre(self):
        return self.__nombre

    def get_edad(self):
        return self.__edad

    def esta_activo(self):
        return self.__activo

    # Setters
    def set_codigo(self, codigo):
        self.__codigo = codigo

    def set_nombre(self, nombre):
        self.__nombre = nombre

    def set_edad(self, edad):
        self.__edad = edad

    def set_activo(self, activo):
        self.__activo = activo

    # Mostrar información básica
    def mostrar_info(self):
        print(f"  Codigo : {self.__codigo}")
        print(f"  Nombre : {self.__nombre}")
        print(f"  Edad   : {self.__edad} años")


# =============================================
#  CLASE GestorCurso
# =============================================
class GestorCurso:

    def __init__(self):
        # Arreglo de tamaño fijo simulado con lista de objetos vacíos
        self.__estudiantes = [Estudiante() for _ in range(MAX_ESTUDIANTES)]
        # Matriz de notas inicializada en -1
        self.__notas = [[-1.0] * NUM_NOTAS for _ in range(MAX_ESTUDIANTES)]
        self.__total_registrados = 0

    # Método auxiliar: busca índice por código (-1 si no existe)
    def __buscar_indice(self, codigo):
        for i in range(MAX_ESTUDIANTES):
            if self.__estudiantes[i].esta_activo() and self.__estudiantes[i].get_codigo() == codigo:
                return i
        return -1

    # Método auxiliar: primer slot libre (-1 si está lleno)
    def __primer_slot_libre(self):
        for i in range(MAX_ESTUDIANTES):
            if not self.__estudiantes[i].esta_activo():
                return i
        return -1

    # 1. Registrar estudiante
    def registrar_estudiante(self):
        if self.__total_registrados >= MAX_ESTUDIANTES:
            print("\n  [!] El curso esta lleno. No se pueden registrar mas estudiantes.")
            return

        slot = self.__primer_slot_libre()
        print("\n--- Registrar Estudiante ---")

        # Validar código
        while True:
            try:
                cod = int(input("  Codigo (numero positivo): "))
                if cod <= 0:
                    print("  Codigo invalido. Ingrese un numero positivo.")
                    continue
                break
            except ValueError:
                print("  Codigo invalido. Ingrese un numero positivo.")

        if self.__buscar_indice(cod) != -1:
            print("  [!] Ya existe un estudiante con ese codigo.")
            return

        # Validar nombre
        while True:
            nom = input("  Nombre: ").strip()
            if nom == "":
                print("  El nombre no puede estar vacio.")
            else:
                break

        # Validar edad
        while True:
            try:
                eda = int(input("  Edad (entre 14 y 99): "))
                if eda < 14 or eda > 99:
                    print("  Edad invalida. Ingrese entre 14 y 99.")
                    continue
                break
            except ValueError:
                print("  Edad invalida. Ingrese un numero.")

        self.__estudiantes[slot] = Estudiante(cod, nom, eda, activo=True)
        self.__total_registrados += 1
        print("  [OK] Estudiante registrado exitosamente.")

    # 2. Mostrar todos los estudiantes
    def mostrar_todos(self):
        print("\n--- Lista de Estudiantes ---")
        if self.__total_registrados == 0:
            print("  No hay estudiantes registrados.")
            return
        count = 1
        for i in range(MAX_ESTUDIANTES):
            if self.__estudiantes[i].esta_activo():
                print(f"\n  Estudiante #{count}:")
                self.__estudiantes[i].mostrar_info()
                count += 1

    # 3. Buscar estudiante por código
    def buscar_estudiante(self):
        print("\n--- Buscar Estudiante ---")
        while True:
            try:
                cod = int(input("  Ingrese el codigo: "))
                if cod <= 0:
                    print("  Codigo invalido.")
                    continue
                break
            except ValueError:
                print("  Codigo invalido.")

        idx = self.__buscar_indice(cod)
        if idx == -1:
            print("  [!] No se encontro ningun estudiante con ese codigo.")
        else:
            print("\n  Estudiante encontrado:")
            self.__estudiantes[idx].mostrar_info()

    # 4. Asignar / actualizar notas
    def asignar_notas(self):
        print("\n--- Asignar Notas ---")
        while True:
            try:
                cod = int(input("  Ingrese el codigo del estudiante: "))
                if cod <= 0:
                    print("  Codigo invalido.")
                    continue
                break
            except ValueError:
                print("  Codigo invalido.")

        idx = self.__buscar_indice(cod)
        if idx == -1:
            print("  [!] Estudiante no encontrado.")
            return

        print(f"  Ingresando {NUM_NOTAS} notas para {self.__estudiantes[idx].get_nombre()}:")
        for j in range(NUM_NOTAS):
            while True:
                try:
                    nota = float(input(f"    Nota {j + 1} (0.0 - 5.0): "))
                    if nota < 0.0 or nota > 5.0:
                        print("    Nota invalida. Ingrese entre 0.0 y 5.0.")
                        continue
                    break
                except ValueError:
                    print("    Nota invalida. Ingrese un numero.")
            self.__notas[idx][j] = nota
        print("  [OK] Notas asignadas correctamente.")

    # 5. Mostrar promedio de un estudiante
    def mostrar_promedio(self):
        print("\n--- Promedio de Estudiante ---")
        while True:
            try:
                cod = int(input("  Ingrese el codigo: "))
                if cod <= 0:
                    print("  Codigo invalido.")
                    continue
                break
            except ValueError:
                print("  Codigo invalido.")

        idx = self.__buscar_indice(cod)
        if idx == -1:
            print("  [!] Estudiante no encontrado.")
            return

        tiene_notas = all(self.__notas[idx][j] >= 0 for j in range(NUM_NOTAS))
        if not tiene_notas:
            print("  [!] Este estudiante no tiene todas sus notas asignadas.")
            return

        promedio = sum(self.__notas[idx]) / NUM_NOTAS
        print(f"  Estudiante : {self.__estudiantes[idx].get_nombre()}")
        print(f"  Promedio   : {promedio:.1f}", end="")
        if promedio >= 3.0:
            print("  -> APROBADO")
        else:
            print("  -> REPROBADO")

    # 6. Mostrar matriz completa de notas
    def mostrar_matriz_notas(self):
        print("\n--- Matriz de Notas ---")
        if self.__total_registrados == 0:
            print("  No hay estudiantes registrados.")
            return

        # Encabezado
        print(f"  {'Codigo':<8}{'Nombre':<22}{'Nota1':>8}{'Nota2':>8}{'Nota3':>8}")
        print("  " + "-" * 54)

        for i in range(MAX_ESTUDIANTES):
            if self.__estudiantes[i].esta_activo():
                cod = str(self.__estudiantes[i].get_codigo())
                nom = self.__estudiantes[i].get_nombre()
                fila = f"  {cod:<8}{nom:<22}"
                for j in range(NUM_NOTAS):
                    if self.__notas[i][j] < 0:
                        fila += f"{'N/A':>8}"
                    else:
                        fila += f"{self.__notas[i][j]:>8.1f}"
                print(fila)


# =============================================
#  FUNCIÓN PRINCIPAL
# =============================================
def main():
    curso = GestorCurso()

    print("============================================")
    print("  Bienvenido al Sistema de Gestion de      ")
    print("  Estudiantes y Calificaciones             ")
    print("  Programacion Orientada a Objetos - Python")
    print("============================================")

    while True:
        print("\n========== MENU PRINCIPAL ==========")
        print("  1. Registrar estudiante")
        print("  2. Mostrar todos los estudiantes")
        print("  3. Buscar estudiante por codigo")
        print("  4. Asignar / actualizar notas")
        print("  5. Mostrar promedio de un estudiante")
        print("  6. Mostrar matriz completa de notas")
        print("  7. Salir")
        print("====================================")

        try:
            opcion = int(input("  Seleccione una opcion: "))
        except ValueError:
            print("  [!] Opcion invalida. Intente de nuevo.")
            continue

        if opcion == 1:
            curso.registrar_estudiante()
        elif opcion == 2:
            curso.mostrar_todos()
        elif opcion == 3:
            curso.buscar_estudiante()
        elif opcion == 4:
            curso.asignar_notas()
        elif opcion == 5:
            curso.mostrar_promedio()
        elif opcion == 6:
            curso.mostrar_matriz_notas()
        elif opcion == 7:
            print("\n  Hasta luego. Cerrando el sistema...")
            break
        else:
            print("  [!] Opcion no valida. Elija entre 1 y 7.")


if __name__ == "__main__":
    main()
