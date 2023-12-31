﻿/*****************************************************************************
 * 
 * ReoGrid - .NET Spreadsheet Control
 * 
 * http://reogrid.net/
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 * Author: Jing <lujing at unvell.com>
 *
 * Copyright (c) 2012-2016 Jing <lujing at unvell.com>
 * Copyright (c) 2012-2016 unvell.com, all rights reserved.
 * 
 ****************************************************************************/

using System;
using System.Collections.Generic;
using System.Reflection;
using System.Linq;

using System.Windows.Forms;
using RGFloat = System.Single;
using RGImage = System.Drawing.Image;

namespace unvell.ReoGrid.CellTypes
{
	/// <summary>
	/// Representation of a typecial dropdown control on spreadsheet
	/// </summary>
	public class DropdownListCell : DropdownCell
	{
		/// <summary>
		/// Construct dropdown control with an empty items list
		/// </summary>
		public DropdownListCell()
			: base()
		{
			this.listData = new List<object>(0);
		}

		/// <summary>
		/// Construct dropdown control with specified items array
		/// </summary>
		/// <param name="items">candidate object array to be displayed in the listbox</param>
		public DropdownListCell(params object[] items)
			: this()
		{
			this.listData.AddRange(items);
		}

		/// <summary>
		/// Construct dropdown control with specified items array
		/// </summary>
		/// <param name="items">candidate object array to be displayed in the listbox</param>
		public DropdownListCell(IEnumerable<object> items)
			: this()
		{
			this.listData.AddRange(items);
		}

		/// <summary>
		/// Get or set the selected index in items list
		/// </summary>
		public int SelectedIndex
		{
			get
			{
				return this.listBox.SelectedIndex;
			}
			set
			{
				this.listBox.SelectedIndex = value;
			}
		}

		/// <summary>
		/// Set selected item
		/// </summary>
		/// <param name="obj">Selected item to be handled</param>
		protected virtual void SetSelectedItem(object obj)
		{
			SelectedItem = obj;

			this.SelectedItemChanged?.Invoke(this, null);
		}

		/// <summary>
		/// Event for selected item changed
		/// </summary>
		public event EventHandler SelectedItemChanged;

		private List<object> listData;

		public IEnumerable<object> ListData
		{
			get { return listData; }
			set
			{
				if (!value.SequenceEqual(ListData))
				{
					listData = new List<object>(value);

					if (listBox != null)
					{
						listBox.Items.Clear();
						listBox.Items.AddRange(this.listData.ToArray());
					}

					this.Cell.Worksheet.RaiseCellDataChangedEvent(this.Cell);
				}
			}
		}

		/// <summary>
		/// Push down the dropdown panel.
		/// </summary>
		public override void PushDown()
		{
			if (this.listBox == null)
			{
				this.listBox = new ListBox()
				{
					Dock = DockStyle.Fill,
					BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle,
				};

				listBox.Click += ListBox_Click;
				listBox.KeyDown += ListBox_KeyDown;
				listBox.MouseMove += (sender, e) =>
				{
					int index = listBox.IndexFromPoint(e.Location);
					if (index != -1) listBox.SelectedIndex = index;
				};

				if (this.listData != null)
				{
					listBox.Items.AddRange(this.listData.ToArray());
				}

				base.DropdownControl = listBox;

				if (listBox.Items.Count > 0)
					base.DropdownPanelHeight = Math.Min(200, (listBox.Items.Count * listBox.GetItemRectangle(0).Height) + 6);
			}

			listBox.SelectedItem = this.Cell.InnerData;

			base.PushDown();
		}

		private ListBox listBox;

		void ListBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (base.Cell != null && base.Cell.Worksheet != null)
			{
				if ((e.KeyCode == Keys.Enter || e.KeyCode == Keys.Space))
				{
					SetSelectedItem(this.listBox.SelectedItem);
					PullUp();
				}
				else if (e.KeyCode == Keys.Escape)
				{
					PullUp();
				}
			}
		}

		void ListBox_Click(object sender, EventArgs e)
		{
			if (this.Cell != null && this.Cell.Worksheet != null)
			{
				SetSelectedItem(this.listBox.SelectedItem);
			}

			PullUp();
		}

		#region Items Property
		private DropdownItemsCollection itemsCollection;

		/// <summary>
		/// Collection of candidate items
		/// </summary>
		public DropdownItemsCollection Items
		{
			get
			{
				if (this.itemsCollection == null)
				{
					this.itemsCollection = new DropdownItemsCollection(this);
				}

				return this.itemsCollection;
			}
		}
		#endregion // Items Property

		#region DropdownItemsCollection
		/// <summary>
		/// Represents drop-down items collection.
		/// </summary>
		public class DropdownItemsCollection : ICollection<object>
		{
			private DropdownListCell owner;

			internal DropdownItemsCollection(DropdownListCell owner)
			{
				this.owner = owner;
			}

			/// <summary>
			/// Add candidate item.
			/// </summary>
			/// <param name="item">Item to be added.</param>
			public void Add(object item)
			{
				if (this.owner.listBox != null)
				{
					this.owner.listBox.Items.Add(item);
				}
				else
				{
					this.owner.listData.Add(item);
				}
			}

			/// <summary>
			/// Add multiple candidate items.
			/// </summary>
			/// <param name="items">Items to be added.</param>
			public void AddRange(params object[] items)
			{
				if (this.owner.listBox != null)
				{
					this.owner.listBox.Items.AddRange(items);
				}
				else
				{
					this.owner.listData.AddRange(items);
				}
			}

			/// <summary>
			/// Clear all candidate items.
			/// </summary>
			public void Clear()
			{
				if (this.owner.listBox != null)
				{
					this.owner.listBox.Items.Clear();
				}
				else
				{
					this.owner.listData.Clear();
				}
			}

			/// <summary>
			/// Check whether or not the candidate list contains specified item.
			/// </summary>
			/// <param name="item">item to be checked.</param>
			/// <returns>true if contained, otherwise return false.</returns>
			public bool Contains(object item)
			{
				if (this.owner.listBox != null)
				{
					return this.owner.listBox.Items.Contains(item);
				}
				else
				{
					return this.owner.listData.Contains(item);
				}
			}

			/// <summary>
			/// Copy the candidate list into specified array.
			/// </summary>
			/// <param name="array">array to be copied into.</param>
			/// <param name="arrayIndex">number of item to start copy.</param>
			public void CopyTo(object[] array, int arrayIndex)
			{
				if (this.owner.listBox != null)
				{
					this.owner.listBox.Items.CopyTo(array, arrayIndex);
				}
				else
				{
					this.owner.listData.CopyTo(array, arrayIndex);
				}
			}

			/// <summary>
			/// Return the number of items in candidate list.
			/// </summary>
			public int Count
			{
				get
				{
					if (this.owner.listBox != null)
					{
						return this.owner.listBox.Items.Count;
					}
					else
					{
						return this.owner.listData.Count;
					}
				}
			}

			/// <summary>
			/// Check whether or not the candidate list is read-only.
			/// </summary>
			public bool IsReadOnly
			{
				get
				{
					if (this.owner.listBox != null)
					{
						return this.owner.listBox.Items.IsReadOnly;
					}
					else
					{
						return false;
					}
				}
			}

			/// <summary>
			/// Remove specified item from candidate list.
			/// </summary>
			/// <param name="item">item to be removed.</param>
			/// <returns>true if item has been removed successfully.</returns>
			public bool Remove(object item)
			{
				if (this.owner.listBox != null)
				{
					this.owner.listBox.Items.Remove(item);
					return true;
				}
				else
				{
					return this.owner.listData.Remove(item);
				}
			}

			/// <summary>
			/// Get enumerator of candidate list.
			/// </summary>
			/// <returns>enumerator of candidate list.</returns>
			public IEnumerator<object> GetEnumerator()
			{
				if (this.owner.listBox != null)
				{
					var items = this.owner.listBox.Items;
					foreach (var item in items)
					{
						yield return item;
					}
				}
				else
				{
					foreach (var item in this.owner.listData)
						yield return item;
				}
			}

			/// <summary>
			/// Get enumerator of candidate list.
			/// </summary>
			/// <returns>enumerator of candidate list.</returns>
			System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
			{
				if (this.owner.listBox != null)
				{
					var items = this.owner.listBox.Items;

					foreach (var item in items)
					{
						yield return item;
					}
				}
				else
				{
					foreach (var item in this.owner.listData)
					{
						yield return item;
					}
				}
			}
		}
		#endregion // DropdownItemsCollection

		/// <summary>
		/// Clone a drop-down list from this object.
		/// </summary>
		/// <returns>New instance of dropdown list.</returns>
		public override ICellBody Clone()
		{
			return new DropdownListCell(this.listData);
		}
	}
}
