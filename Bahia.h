#pragma once
using namespace System;
#include "Estructuras.h"
#include "Item.h"
namespace BodegaGrid {

	public ref class Bahia
	{
	private:
		//posicion en el plano
		char fila;
		int columna;
		//ID de la bahia
		String^ Id;
		//lista de productos que puede contener la bahia
		List<int>^ ID_productos;
		//lista de items que tiene la bahia (en cola para no perder lo de la antigüedad)
		List<Queue<Item^>^>^ items;
		//peso total que puede retener la bahia
		double peso_max;
		//peso usado
		double peso_actual;
		//verifica si la bahia ya está llena
		bool completo;
		//proceso de verificacion
		void filled() {
			if (peso_max == peso_actual) {
				completo = true;
			}
			else {
				completo = false;
			}
		}
		//item eliminado y agregado (para acceder a el más facil)
		Item^ itemeliminado;
		Item^ itemagregado;
	public:
		//constructor
		Bahia() {
			Id = "";
			peso_max = 0;
			ID_productos = gcnew List<int>;
			peso_actual = 0;
			completo = false;
			items = gcnew List<Queue<Item^>^>;
			itemeliminado = gcnew Item();
			itemagregado = gcnew Item();
		}
		//getters
		property String^ ID {
			String^ get() {
				return this->Id;
			}
		}
		property bool Filled {
			bool get() {
				filled();
				return completo;
			}
		}
		property int Fila {
			int get() {
				return fila;
			}
		}
		property int Columna {
			int get() {
				return columna;
			}
		}
		property List<int>^ Product {
			List<int>^ get() {
				return ID_productos;
			}
		}
		property double MaxWeight {
			double get() {
				return peso_max;
			}
		}
		property double ActWeight {
			double get() {
				return peso_actual;
			}
		}
		property List<Queue<Item^>^>^ Items {
			List<Queue<Item^>^>^ get() {
				return items;
			}
		}
		property Item^ I_eliminado {
			Item^ get() {
				return itemeliminado;
			}
		}
		property Item^ I_agregado {
			Item^ get() {
				return itemagregado;
			}
		}
		//setters
		void SetPos(int columna, int fila) {
			this->columna = columna;
			this->fila = fila;
		}
		void SetID(String^ fila, String^ columna) {
			Id = fila + columna;
		}
		void SetMaxWeight(double max) {
			peso_max = max;
		}
		void SetActWeight(double actual) {
			peso_actual += actual;
		}
		void SetItems(Item^ newitems) {
			Queue<Item^>^ newQueue = gcnew Queue<Item^>;
			bool tiponuevo = true;
			//si la lista está vacia se inicializa y llena con el primer elemento que entre
			if (items[0] == nullptr) {
				items->Add(newQueue);
				items[0]->Enqueue(newitems);
				itemagregado = newitems;
			}
			else {
				//de lo contrario, busca en que posicion de la lista se encuentra la cola con el mismo tipo de item
				for (int i = 0; i < items->Count(); i++)
				{
					if (items[i]->Peek()->Type == newitems->Type) {
						items[i]->Enqueue(newitems);
						itemagregado = newitems;
						tiponuevo = false;
						break;
					}
					else {
						// si no encuentra significa que es un tipo nuevo de item 
						tiponuevo = true;
						if (items->Count() == 1) {
							break;
						}
					}
				}
				//si no se encontró dentro de la lista se crea una nueva posicion en la lista
				if (tiponuevo) {
					items->Add(newQueue);
					items[items->Count() - 1]->Enqueue(newitems);
					itemagregado = newitems;
				}
				//ordenamiento dentro de la lista (1,2,3)
				if (items->Count() > 1 && tiponuevo) {
					for (int i = 0; i < items->Count() - 1; i++)
					{
						for (int j = 0; j < items->Count() - i - 1; j++)
						{
							if (items[j]->Peek()->Type > items[j + 1]->Peek()->Type) {
								newQueue = items[j];
								items[j] = items[j + 1];
								items[j + 1] = newQueue;
							}
						}
					}
				}
			}
		}
		void SetIDProducto(int producto) {
			ID_productos->Add(producto);
		}
		//procesos
		//removedor de items
		int RemoveItems(int cant, int type) {
			int pos = -1;
			int residuo;
			//busca dentro de las colas la posicon de la lista que contenga el tipo de item a eliminar y lo guarda
			for (int i = 0; i < items->Count(); i++)
			{
				if (items[i]->Peek()->Type == type) {
					pos = i;
					break;
				}
			}
			if (pos != -1) {
				//si lo encuentra y los items de la cola son menor a la cantidad a eliminar solo se resta
				if (items[pos]->Peek()->Unidades > cant) {
					residuo = items[pos]->Peek()->Unidades - cant;
					items[pos]->Peek()->SetUnits(residuo);
					itemeliminado = items[pos]->Peek();
					return cant;
				}
				// de lo contrario, quita el elemento de la cola y devuelve el valor eliminado
				else {
					if (items[pos]->Count() != 1 || items[pos]->Peek()->Unidades <= cant) {
						int eliminados = items[pos]->Peek()->Unidades;
						itemeliminado = items[pos]->Dequeue();
						return eliminados;
					}
					else {
						//si lo que se quiere eliminar sobrepasa lo que existe
						throw gcnew System::IndexOutOfRangeException;
					}
				}
			}
			else {
				//si no lo encuentra, error
				throw gcnew System::IndexOutOfRangeException;
			}
		}
		//intenta llenar la bahia con el peso entrante
		bool Try_fill(double try_weight) {
			int trypeso = peso_actual + try_weight;
			if (trypeso > peso_max) {
				return false;
			}
			else {
				return true;
			}
		}
		//devuelve el index de la lista que contiene el tipo de item indicado
		int IndexOfType(int tipo) {
			for (int i = 0; i < items->Count(); i++)
			{
				try {
					if (items[i]->Peek()->Type == tipo) {
						return i;
					}
				}
				catch (Exception^) {
					return -1;
				}
			}
			throw gcnew System::IndexOutOfRangeException;
		}
	};
}