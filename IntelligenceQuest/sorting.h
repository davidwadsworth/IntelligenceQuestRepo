#pragma once
#include "collider.h"
#include <vector>

namespace Sorts
{
	template <class T>
	static int insertion_sort(T arr[], int n)
	{
		int i, key, j;
		for (i = 1; i < n; i++)
		{
			key = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}

	static void sort_colliders(std::vector<Collider*> collision_objs, Collider * collider)
	{
		int i, j;
		Collider * key;

		for (i = 1; i < collision_objs.size(); i++)
		{
			key = collision_objs[i];
			j = i - 1;

			while (j >= 0 &&
				glm::dot(collision_objs[j]->get_center(), collider->get_center()) > glm::dot(key->get_center(), collider->get_center()))
			{
				collision_objs[j + 1] = collision_objs[j];
				j = j - 1;
			}

			collision_objs[j + 1] = key;
		}
	}


	template<class T>
	class merge_sort
	{
		static void merge(T arr[], int l, int m, int r)
		{
			int i, j, k;
			int n1 = m - l + 1;
			int n2 = r - m;

			/* create temp arrays */
			int L[n1], R[n2];

			/* Copy data to temp arrays L[] and R[] */
			for (i = 0; i < n1; i++)
				L[i] = arr[l + i];
			for (j = 0; j < n2; j++)
				R[j] = arr[m + 1 + j];

			/* Merge the temp arrays back into arr[l..r]*/
			i = 0; // Initial index of first subarray 
			j = 0; // Initial index of second subarray 
			k = l; // Initial index of merged subarray 
			while (i < n1 && j < n2)
			{
				if (L[i] <= R[j])
				{
					arr[k] = L[i];
					i++;
				}
				else
				{
					arr[k] = R[j];
					j++;
				}
				k++;
			}

			/* Copy the remaining elements of L[], if there
			   are any */
			while (i < n1)
			{
				arr[k] = L[i];
				i++;
				k++;
			}

			/* Copy the remaining elements of R[], if there
			   are any */
			while (j < n2)
			{
				arr[k] = R[j];
				j++;
				k++;
			}
		}
	public:
		void sort(T arr[], int l, int r)
		{
			if (l < r)
			{
				// Same as (l+r)/2, but avoids overflow for 
				// large l and h 
				int m = l + (r - l) / 2;

				// Sort first and second halves 
				sort(arr, l, m);
				sort(arr, m + 1, r);

				merge(arr, l, m, r);
			}
		}
	};
}