#pragma once
using namespace System;
#include"KardexInventario.h"
#include "Bodega.h"

namespace BodegaGrid {
	public ref class Ordenar {
	private:
		//posicion actual
		int actual;
		//kardex
		Kardex^ newkard;
		//total
		int total;
		//movimientos
		int added;
		int remove;
		int deleted;
	public:
		Ordenar() {
			actual = -1;
			total = 0;
			added = 1;
			remove = 1;
			deleted = 1;
		}
		//ASCII de la sila
		int PosicionarVector(char pos) {
			for (int i = 65; i < 91; i++)
			{
				if (i == pos) {
					actual++;
					return actual;
				}
				else {
					actual++;
				}
			}
			return actual;
		}
		//creacion de elemento de kardex
		void NewKardex(String^ responsable, String^ Entrada, String^ Salida, String^ movimiento, double price_u, int cant, Bodega^ Bodeguita) {
			newkard = gcnew Kardex();
			DateTime fecha = DateTime::Today;
			String^ formato = gcnew String(fecha.ToString("dd/MM/yyyy"));
			if (movimiento == "Agregar") {
				newkard->SetCode(Salida + "A" + added + Entrada);
				newkard->SetPrice(price_u);
				newkard->SetSalidaEntrada(Salida, Entrada);
				newkard->SetQuantity(cant);
				newkard->SetTotal(price_u * cant + total);
				added++;
			}
			if (movimiento == "Items removidos") {
				newkard->SetCode(Salida + "R" + remove + Entrada);
				newkard->SetPrice(price_u);
				newkard->SetSalidaEntrada(Salida, Entrada);
				newkard->SetQuantity(cant);
				newkard->SetTotal(price_u * cant + total);
				remove++;
			}
			if (movimiento == "Bahia eliminada") {
				newkard->SetCode(Salida + "DELETED" + deleted);
				deleted++;
			}
			newkard->SetDate(formato);
			newkard->SetMovement(movimiento);
			newkard->SetResponsible(responsable);
			total += price_u * cant;
			Bodeguita->SetKardex(newkard);
		}
		//creacion de elemento de inventario
		void NewStock(int tipo, int cantidad, double price, Bodega^ Bodeguita) {
			Inventario^ adstock = gcnew Inventario();
			adstock->SetType(tipo);
			adstock->SetUnits(cantidad);
			adstock->SetFinalCost(price * cantidad);
			if (Bodeguita->InventarioStack[0] == nullptr) {
				Bodeguita->InventarioStack->Add(adstock);
			}
			else {
				for (int i = 0; i < Bodeguita->InventarioStack->Count(); i++)
				{
					if (Bodeguita->InventarioStack[i]->Type == tipo) {
						Bodeguita->InventarioStack[i]->SetType(tipo);
						Bodeguita->InventarioStack[i]->SetUnits(cantidad);
						Bodeguita->InventarioStack[i]->SetFinalCost(price * cantidad);
						break;
					}
					else if (i == Bodeguita->InventarioStack->Count() - 1) {
						Bodeguita->InventarioStack->Add(adstock);
						break;
					}
				}
			}
		}
		//ordenamientos de inventario
		void OrdenarTipo(Bodega^ Bodeguita) {
			for (int i = 0; i < Bodeguita->InventarioStack->Count() - 1; i++)
			{
				for (int j = 0; j < Bodeguita->InventarioStack->Count() - 1 - i; j++)
				{
					if (Bodeguita->InventarioStack[j]->Type > Bodeguita->InventarioStack[j + 1]->Type) {
						Inventario^ aux = gcnew Inventario();
						aux = Bodeguita->InventarioStack[j];
						Bodeguita->InventarioStack[j] = Bodeguita->InventarioStack[j + 1];
						Bodeguita->InventarioStack[j + 1] = aux;
					}
				}
			}
		}
		void OrdenarPrecio(Bodega^ Bodeguita) {
			for (int i = 0; i < Bodeguita->InventarioStack->Count() - 1; i++)
			{
				for (int j = 0; j < Bodeguita->InventarioStack->Count() - 1 - i; j++)
				{
					if (Bodeguita->InventarioStack[j]->Price > Bodeguita->InventarioStack[j + 1]->Price) {
						Inventario^ aux = gcnew Inventario();
						aux = Bodeguita->InventarioStack[j];
						Bodeguita->InventarioStack[j] = Bodeguita->InventarioStack[j + 1];
						Bodeguita->InventarioStack[j + 1] = aux;
					}
				}
			}
		}
		void OrdenarCantidad(Bodega^ Bodeguita) {
			for (int i = 0; i < Bodeguita->InventarioStack->Count() - 1; i++)
			{
				for (int j = 0; j < Bodeguita->InventarioStack->Count() - 1 - i; j++)
				{
					if (Bodeguita->InventarioStack[i]->Units > Bodeguita->InventarioStack[j + 1]->Units) {
						Inventario^ aux = gcnew Inventario();
						aux = Bodeguita->InventarioStack[j];
						Bodeguita->InventarioStack[j] = Bodeguita->InventarioStack[j + 1];
						Bodeguita->InventarioStack[j + 1] = aux;
					}
				}
			}
		}
	};
}