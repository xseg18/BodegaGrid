#pragma once
#include "Estructuras.h"
#include "KardexInventario.h"
#include "Bahia.h"

namespace BodegaGrid {

	public ref class Bodega {
	private:
		//array de bahias
		cli::array<List<Bahia^>^>^ bahias;
		//lista de inventario
		List<Inventario^>^ inventario;
		//pila de kardex
		Stack<Kardex^>^ kardex;
	public:
		//constructores
		Bodega() {
			bahias = gcnew cli::array<List<Bahia^>^>(27);
			kardex = gcnew Stack<Kardex^>();
			inventario = gcnew List<Inventario^>();
		}
		//getters
		property  cli::array<List<Bahia^>^>^ Bahias {
			cli::array<List<Bahia^>^>^ get() {
				return bahias;
			}
		}
		property Stack<Kardex^>^ KardexStack {
			Stack<Kardex^>^ get() {
				return kardex;
			}
		}
		property List<Inventario^>^ InventarioStack {
			List<Inventario^>^ get() {
				return inventario;
			}
		}
		//setters
		void SetBahia(Bahia^ bahia) {
			if (bahias[bahia->Fila] == nullptr) {
				bahias[bahia->Fila] = gcnew List<Bahia^>;
				for (int i = 0; i < bahia->Columna; i++)
				{
					Bahia^ newbay = gcnew Bahia;
					bahias[bahia->Fila]->Add(newbay);
				}
				if (bahias[bahia->Fila][bahia->Columna - 1]->ID == "") {
					bahias[bahia->Fila][bahia->Columna - 1] = bahia;
				}
				else {
					throw gcnew System::FormatException;
				}
			}
			else {
				if (bahia->Columna > bahias[bahia->Fila]->Count()) {
					for (int i = bahias[bahia->Fila]->Count(); i < bahia->Columna; i++)
					{
						Bahia^ newbay = gcnew Bahia;
						bahias[bahia->Fila]->Add(newbay);
					}
				}
				if (bahias[bahia->Fila][bahia->Columna - 1]->ID == "") {
					bahias[bahia->Fila][bahia->Columna - 1] = bahia;
				}
				else {
					throw gcnew System::FormatException;
				}bahias[bahia->Fila][bahia->Columna - 1] = bahia;
			}
		}
		void SetKardex(Kardex^ Kardex) {
			kardex->Push(Kardex);
		}
		//borrar bahia
		int DeleteBahia(int fila, int columna, int item) {
			if (bahias[fila] == nullptr) {
				throw gcnew System::IndexOutOfRangeException();
			}
			else if (bahias[fila][columna - 1]->Filled || bahias[fila][columna - 1]->ActWeight != 0) {
				if (item < 1) {
					if (bahias[fila][columna - 1]->Product->Contains(1) && bahias[fila][columna - 1]->Items[bahias[fila][columna - 1]->IndexOfType(1)]->Peek() != nullptr) {
						return 1;
					}
				}
				if (item < 2) {
					if (bahias[fila][columna - 1]->Product->Contains(2) && bahias[fila][columna - 1]->Items[bahias[fila][columna - 1]->IndexOfType(2)]->Peek()->Unidades != 0) {
						return 2;
					}
				}
				if (item < 3) {
					if (bahias[fila][columna - 1]->Product->Contains(3) && bahias[fila][columna - 1]->Items[bahias[fila][columna - 1]->IndexOfType(3)]->Peek()->Unidades != 0) {
						return 3;
					}
				}
			}
			else {
				delete bahias[fila][columna - 1];
				bahias[fila][columna - 1] = gcnew Bahia();
				return -1;
			}
		}
	};
}