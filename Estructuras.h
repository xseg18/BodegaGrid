#pragma once
using namespace System;

namespace BodegaGrid {
	//estructura lineal de lista (Bahias)
	generic <typename T>
		public ref class List {
			ref struct Node {
				T data;
				Node^ siguiente;
				property T Equals {
					T get() {
						return data;
					}
				}
			};
			Node^ top = nullptr;
		public:void Add(T item) {
			Node^ agregar = gcnew Node();
			agregar->siguiente = nullptr;
			agregar->data = item;
			if (!top)
			{
				top = agregar;
			}
			else
			{
				Node^ temp = top;
				while (temp->siguiente)
				{
					temp = temp->siguiente;
				}
				temp->siguiente = agregar;
			}
		}
		public:int Count() {
			int contador = 0;
			Node^ count = top;
			while (count != nullptr) {
				contador++;
				count = count->siguiente;
			}
			return contador;
		}
		public: bool RemoveAt(int index)
		{
			Node^ temp = top;
			Node^ prev = nullptr;

			if (index >= 0 && index < Count())
			{
				if (index == 0)
				{
					top = temp->siguiente;
					return true;
				}
				else
				{
					for (int a = 0; a < index; a++)
					{
						prev = temp;
						temp = temp->siguiente;
					}
					prev->siguiente = temp->siguiente;
					return true;
				}
			}
			else
			{
				throw gcnew System::ArgumentOutOfRangeException("Index fuera del limite de la lista");
			}
		}
		public:void Clear() {
			Node^ aux = gcnew Node();
			Node^ siguiente;
			while (aux != nullptr) {
				siguiente = aux->siguiente;
				delete aux;
				aux = siguiente;
			}
		}
		public:int IndexOf(T item) {
			int pos = -1;
			Node^ actual = gcnew Node();
			actual->siguiente = top;
			Node^ obtener = gcnew Node();
			obtener->data = item;
			while (actual->siguiente != nullptr) {
				try {
					if (actual->data->Equals(obtener->data)) {
						pos++;
						return pos;
					}
					else {
						actual = actual->siguiente;
						pos++;
					}
				}
				catch (Exception^) {
					actual = actual->siguiente;
					if (actual->data->Equals(obtener->data)) {
						pos++;
						return pos;
					}
					else {
						actual = actual->siguiente;
						pos++;
					}
				}
			}
			return -1;
		}
		public: void Foreach(Action<T>^ action) {
			Node^ temp = top;
			while (temp) {
				action(temp->data);
				temp = temp->siguiente;
			}
		}
		public: property T default[int]{
			T get(int index) {
				Node^ temp = top;
				int cont = 0;
				while (temp) {
					if (cont == index) {
						return temp->data;
					}
					else {
						temp = temp->siguiente;
						cont++;
					}
				}
			}
			void set(int index, T value) {
				Node^ temp = top;
				int cont = 0;
				while (temp) {
					if (cont == index) {
						temp->data = value;
						break;
					}
					else {
						temp = temp->siguiente;
						cont++;
					}
				}

			}
		}
		public: cli::array<T>^ ToArray() {

			cli::array<T>^ arrayy = gcnew cli::array<T>(Count());
			Node^ temp = top;
			for (int i = 0; i < Count(); i++)
			{
				arrayy[i] = temp->data;
				temp = temp->siguiente;
			}
			return arrayy;
		}
		public: bool Contains(T item) {
			Node^ temp = top;
			for (int i = 0; i < Count(); i++)
			{
				if (temp->data->Equals(item)) {
					return true;
				}
				else {
					temp = temp->siguiente;
				}
			}
			return false;
		}
		};
		//pila (Kardex)
		generic <typename T>
			public ref class Stack
			{
				ref struct Node {
					T data;
					Node^ siguiente;
				};
				Node^ top = nullptr;
			public:
				void Push(T item) {
					Node^ agregar = gcnew Node();
					agregar->data = item;
					agregar->siguiente = nullptr;
					if (!top) {
						top = agregar;
					}
					else {
						agregar->siguiente = top;
						top = agregar;
					}
				}
				T Pop() {
					T devolucion = top->data;
					top = top->siguiente;
					return devolucion;
				}
				T Peek() {
					if (top) {
						T devolucion = top->data;
						return devolucion;
					}
				}
				int Count() {
					int contador = 0;
					Node^ count = top;
					while (count) {
						contador++;
						count = count->siguiente;
					}
					return contador;
				}
				void Clear() {
					Node^ aux = top;
					Node^ siguiente;
					while (aux) {
						siguiente = aux->siguiente;
						delete aux;
						aux = siguiente;
					}
				}
			public: cli::array<T>^ ToArray() {
				cli::array<T>^ arrayy = gcnew cli::array<T>(Count());
				Node^ temp = top;
				for (int i = 0; i < Count(); i++)
				{
					arrayy[i] = temp->data;
					temp = temp->siguiente;
				}
				return arrayy;
			}
			};
			//cola (items)
			generic <typename T>
				public ref class Queue {
					ref struct Node {
						T data;
						Node^ siguiente;
					};
					Node^ top;
					Node^ tail;
				public:
					void Enqueue(T encolar) {
						Node^ temp = gcnew Node();
						temp->data = encolar;
						temp->siguiente = nullptr;
						if (!top) {
							top = temp;
						}
						else
						{
							tail->siguiente = temp;
						}
						tail = temp;
					}
					T Dequeue() {
						if (top) {
							Node^ temp = top;
							T devolución = temp->data;
							top = top->siguiente;
							return devolución;
						}
						else {
							throw gcnew System::ArgumentNullException("Cabeza no encontrada");
						}
					}
					T Peek() {
						if (top) {
							return top->data;
						}
						else {
							throw gcnew System::ArgumentNullException("Cabeza no encontrada");
						}
					}
					int Count() {
						int cont = 0;
						Node^ temp = top;
						while (temp != nullptr) {
							temp = temp->siguiente;
							cont++;
						}
						return cont;
					}
					cli::array<T>^ ToArray() {
						cli::array<T>^ arrayy = gcnew cli::array<T>(Count());
						Node^ temp = top;
						for (int i = 0; i < Count(); i++)
						{
							arrayy[i] = temp->data;
							temp = temp->siguiente;
						}
						return arrayy;
					}
				};
}