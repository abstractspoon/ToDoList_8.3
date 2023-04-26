﻿using System;
using System.Diagnostics;
using System.Collections.Generic;

using Abstractspoon.Tdl.PluginHelpers;

///////////////////////////////////////////////////////////////////////////

namespace EvidenceBoardUIExtension
{
	[System.ComponentModel.DesignerCategory("")]
	class EvidenceBoardLinkVisibilityComboBox : CustomComboBox.CheckedComboBox
	{
		class EvidenceBoardLinkVisibilityItem : TDLNodeControl.LinkType
		{
			public EvidenceBoardLinkVisibilityItem(Translator trans, string label, EvidenceBoardLinkType type)
				:
				base(label, type)
			{
				m_Trans = trans;
			}

			public override string ToString()
			{
				if ((m_Trans != null) && (Type == EvidenceBoardLinkType.User))
					return string.Format(m_Trans.Translate("{0} (User Type)"), Name);

				return Name;
			}

			private Translator m_Trans;
		}

		// ----------------------------------------------------------------

		Translator m_Trans;
		List<string> m_UserTypes = new List<string>();

		class LinkTypeVisibility : TDLNodeControl.LinkType
		{
			public LinkTypeVisibility(string label, EvidenceBoardLinkType type)
				:
				base(label, type)
			{
			}

			public LinkTypeVisibility(TDLNodeControl.LinkType other)
				:
				base(other.Name, other.Type)
			{
			}

			public bool Visible = true;
		}
		List<LinkTypeVisibility> m_PrevLinkVisibility;

		// ----------------------------------------------------------------

		public EvidenceBoardLinkVisibilityComboBox(Translator trans)
		{
			m_Trans = trans;
			None = trans.Translate("<none>");

			UserLinkTypes = null;
			Sorted = true;

			DropDownClosed += (s, e) => { m_PrevLinkVisibility = null; };

		}

		public IEnumerable<string> UserLinkTypes
		{
			get
			{
				return m_UserTypes;
			}

			set
			{
				// Cache the current selection
				var prevVisibility = LinkVisibility;

				// Rebuild the combo
				Items.Clear();

				Items.Add(new EvidenceBoardLinkVisibilityItem(m_Trans, "Dependencies", EvidenceBoardLinkType.Dependency));
				Items.Add(new EvidenceBoardLinkVisibilityItem(m_Trans, "Parent/Child", EvidenceBoardLinkType.ParentChild));

				if (value != null)
				{
					foreach (var name in value)
						Items.Add(new EvidenceBoardLinkVisibilityItem(m_Trans, name, EvidenceBoardLinkType.User));
				}

				// Restore the selection
				for (int index = 0; index < Items.Count; index++)
				{
					var item = (EvidenceBoardLinkVisibilityItem)Items[index];
					var itemVis = prevVisibility.Find(x => ((x.Type == item.Type) && (x.Name == item.Name)));

					ListBox.SetItemChecked(index, ((itemVis == null) ? true : itemVis.Visible));
				}

				m_UserTypes.Clear();

				if (value != null)
					m_UserTypes.AddRange(value);
			}
		}

		private List<LinkTypeVisibility> LinkVisibility
		{
			get
			{
				if (m_PrevLinkVisibility != null)
					return m_PrevLinkVisibility;

				// else
				var linkVis = new List<LinkTypeVisibility>();

				for (int index = 0; index < Items.Count; index++)
				{
					var item = (EvidenceBoardLinkVisibilityItem)Items[index];

					linkVis.Add(new LinkTypeVisibility(item)
					{
						Visible = ListBox.GetItemChecked(index)
					});
				}

				return linkVis;
			}
		}

		private bool IsTypeVisible(List<LinkTypeVisibility> vis, EvidenceBoardLinkType type, string name = "")
		{
			int index = vis.FindIndex(x => ((x.Type == type) && (x.Name == name)));

			return ((index == -1) ? true : vis[index].Visible);
		}

		public List<TDLNodeControl.LinkType> SelectedOptions
		{
			get
			{
				var selOptions = new List<TDLNodeControl.LinkType>();

				foreach (var option in LinkVisibility)
				{
					if (option.Visible)
						selOptions.Add(new TDLNodeControl.LinkType(option.Name, option.Type));
				}

				return selOptions;
			}
		}

		int FindItemIndex(EvidenceBoardLinkType type, string name)
		{
			for (int index = 0; index < Items.Count; index++)
			{
				var item = (EvidenceBoardLinkVisibilityItem)Items[index];

				if ((type == item.Type) && (name == item.Name))
					return index;
			}

			return -1;
		}

		public List<TDLNodeControl.LinkType> LoadPreferences(Preferences prefs, String key)
		{
			var prevVisibility = prefs.GetProfileString(key, "LinkTypeVisibility", "_");

			if (prevVisibility == "_")
			{
				CheckAll();
				m_PrevLinkVisibility = null;
			}
			else
			{
				m_PrevLinkVisibility = new List<LinkTypeVisibility>();

				var options = prevVisibility.Split(new[] { '|' }, StringSplitOptions.RemoveEmptyEntries );

				foreach (var option in options)
				{
					int type = -1;
					string name = string.Empty;

					var parts = option.Split(':');

					if (parts.Length != 3)
					{
						Debug.Assert(false);
						continue;
					}

					if (!int.TryParse(parts[0], out type))
					{
						Debug.Assert(false);
						continue;
					}

					if ((type != (int)EvidenceBoardLinkType.Dependency) && 
						(type != (int)EvidenceBoardLinkType.ParentChild) &&
						(type != (int)EvidenceBoardLinkType.User))
					{
						Debug.Assert(false);
						continue;
					}

					if ((type == (int)EvidenceBoardLinkType.User) && 
						string.IsNullOrWhiteSpace(parts[1]))
					{
						Debug.Assert(false);
						continue;
					}

					int visible = 1;
					int.TryParse(parts[2], out visible);
					
					int find = FindItemIndex((EvidenceBoardLinkType)type, parts[1]);

					if (find != -1)
						ListBox.SetItemChecked(find, (visible != 0));

					m_PrevLinkVisibility.Add(new LinkTypeVisibility(parts[1], (EvidenceBoardLinkType)type)
					{
						Visible = (visible != 0)
					});
				}
			}

			return SelectedOptions;
		}

		public void SavePreferences(Preferences prefs, String key)
		{
			string options = string.Empty;

			for (int index = 0; index < Items.Count; index++)
			{
				bool visible = ListBox.GetItemChecked(index);

				var item = (EvidenceBoardLinkVisibilityItem)Items[index];
				var option = string.Format("{0}:{1}:{2}|", (int)item.Type, item.Name, (visible ? 1 : 0));

				options = options + option;
			}
			
			prefs.WriteProfileString(key, "LinkTypeVisibility", options);
		}
	}

	// ----------------------------------------------------------------------------
}
