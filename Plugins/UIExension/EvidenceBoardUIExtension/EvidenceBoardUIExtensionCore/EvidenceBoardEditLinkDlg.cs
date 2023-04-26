﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Abstractspoon.Tdl.PluginHelpers;

namespace EvidenceBoardUIExtension
{
	public partial class EvidenceBoardEditLinkDlg : Form
	{
		public EvidenceBoardEditLinkDlg(Translator trans, UserLink link, IEnumerable<string> userLinkTypes)
		{
			InitializeComponent();
			
			m_Attribs.SetLink(link);
			m_Attribs.UserLinkTypes = userLinkTypes;

			trans.Translate(this);
		}

		public Color Color { get { return m_Attribs.Color; } }
		public int Thickness { get { return m_Attribs.Thickness; } }
		public UserLink.EndArrows Arrows { get { return m_Attribs.Arrows; } }
		public string Label { get { return m_Attribs.Label; } }
		public string Type { get { return m_Attribs.Type; } }
	}
}
