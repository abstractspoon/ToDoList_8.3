﻿using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EvidenceBoardUIExtension
{
	class EvidenceBoardLinkArrowsComboBox : ComboBox
	{
		class EvidenceBoardArrowsItem
		{
			public EvidenceBoardArrowsItem(string label, UserLinkAttributes.EndArrows arrows)
			{
				Label = label;
				Arrows = arrows;
			}

			public override string ToString()
			{
				return Label;
			}

			public string Label;
			public UserLinkAttributes.EndArrows Arrows { get; private set; }
		}

		// ----------------------------------------------------------------

		public EvidenceBoardLinkArrowsComboBox()
		{
			Items.Add(new EvidenceBoardArrowsItem("None", UserLinkAttributes.EndArrows.None));
			Items.Add(new EvidenceBoardArrowsItem("Start", UserLinkAttributes.EndArrows.Start));
			Items.Add(new EvidenceBoardArrowsItem("End", UserLinkAttributes.EndArrows.Finish));
			Items.Add(new EvidenceBoardArrowsItem("Both", UserLinkAttributes.EndArrows.Both));
		}

		public UserLinkAttributes.EndArrows SelectedOption
		{
			get
			{
				if (SelectedItem != null)
					return (SelectedItem as EvidenceBoardArrowsItem).Arrows;

				// else
				return UserLinkAttributes.EndArrows.None;
			}

			set
			{
				for (int index = 0; index < Items.Count; index++)
				{
					var item = (Items[index] as EvidenceBoardArrowsItem);

					if (item.Arrows == value)
					{
						SelectedItem = item;
						break;
					}
				}
			}
		}
	}

	// ----------------------------------------------------------------------------
}