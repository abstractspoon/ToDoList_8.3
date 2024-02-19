/*****************************************************************************
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
 * ReoGrid and ReoGridEditor is released under MIT license.
 *
 * Copyright (c) 2012-2016 Jing <lujing at unvell.com>
 * Copyright (c) 2012-2016 unvell.com, all rights reserved.
 * 
 ****************************************************************************/

using unvell.UIControls;

namespace unvell.ReoGrid.PropertyPages
{
	partial class BorderPropertyPage
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.grpLine = new System.Windows.Forms.GroupBox();
			this.labStyle = new System.Windows.Forms.Label();
			this.labColor = new System.Windows.Forms.Label();
			this.borderColorSelector = new unvell.UIControls.ColorComboBox();
			this.borderStyleList = new unvell.ReoGrid.PropertyPages.BorderStyleListControl();
			this.borderSetter = new unvell.ReoGrid.PropertyPages.BorderSetterControl();
			this.btnBackslash = new System.Windows.Forms.Button();
			this.btnRight = new System.Windows.Forms.Button();
			this.btnCenter = new System.Windows.Forms.Button();
			this.btnLeft = new System.Windows.Forms.Button();
			this.btnSlash = new System.Windows.Forms.Button();
			this.btnBottom = new System.Windows.Forms.Button();
			this.btnMiddle = new System.Windows.Forms.Button();
			this.btnTop = new System.Windows.Forms.Button();
			this.btnInside = new System.Windows.Forms.Button();
			this.btnOutline = new System.Windows.Forms.Button();
			this.btnNone = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.grpLine.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// grpLine
			// 
			this.grpLine.Controls.Add(this.labStyle);
			this.grpLine.Controls.Add(this.labColor);
			this.grpLine.Controls.Add(this.borderColorSelector);
			this.grpLine.Controls.Add(this.borderStyleList);
			this.grpLine.ForeColor = System.Drawing.SystemColors.WindowText;
			this.grpLine.Location = new System.Drawing.Point(24, 20);
			this.grpLine.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.grpLine.Name = "grpLine";
			this.grpLine.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.grpLine.Size = new System.Drawing.Size(260, 422);
			this.grpLine.TabIndex = 1;
			this.grpLine.TabStop = false;
			this.grpLine.Text = "Line Attributes";
			// 
			// labStyle
			// 
			this.labStyle.AutoSize = true;
			this.labStyle.ForeColor = System.Drawing.SystemColors.WindowText;
			this.labStyle.Location = new System.Drawing.Point(20, 42);
			this.labStyle.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.labStyle.Name = "labStyle";
			this.labStyle.Size = new System.Drawing.Size(44, 20);
			this.labStyle.TabIndex = 3;
			this.labStyle.Text = "Style";
			// 
			// labColor
			// 
			this.labColor.AutoSize = true;
			this.labColor.ForeColor = System.Drawing.SystemColors.WindowText;
			this.labColor.Location = new System.Drawing.Point(20, 335);
			this.labColor.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.labColor.Name = "labColor";
			this.labColor.Size = new System.Drawing.Size(55, 20);
			this.labColor.TabIndex = 2;
			this.labColor.Text = "Colour";
			// 
			// borderColorSelector
			// 
			this.borderColorSelector.BackColor = System.Drawing.SystemColors.Window;
			this.borderColorSelector.CloseOnClick = true;
			this.borderColorSelector.dropdown = false;
			this.borderColorSelector.Location = new System.Drawing.Point(24, 358);
			this.borderColorSelector.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.borderColorSelector.Name = "borderColorSelector";
			this.borderColorSelector.Size = new System.Drawing.Size(206, 35);
			this.borderColorSelector.SolidColor = System.Drawing.Color.Black;
			this.borderColorSelector.TabIndex = 1;
			this.borderColorSelector.Text = "colorComboBox1";
			// 
			// borderStyleList
			// 
			this.borderStyleList.BackColor = System.Drawing.SystemColors.Window;
			this.borderStyleList.BorderColor = System.Drawing.SystemColors.WindowText;
			this.borderStyleList.BorderLineStyle = unvell.ReoGrid.BorderLineStyle.None;
			this.borderStyleList.Location = new System.Drawing.Point(24, 72);
			this.borderStyleList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.borderStyleList.Name = "borderStyleList";
			this.borderStyleList.SelectedBorderStyle = unvell.ReoGrid.BorderLineStyle.Solid;
			this.borderStyleList.Size = new System.Drawing.Size(206, 234);
			this.borderStyleList.TabIndex = 0;
			this.borderStyleList.Text = "borderStyleList1";
			// 
			// borderSetter
			// 
			this.borderSetter.BackColor = System.Drawing.SystemColors.Window;
			this.borderSetter.Cols = 2;
			this.borderSetter.CurrentBorderStlye = unvell.ReoGrid.BorderLineStyle.None;
			this.borderSetter.CurrentColor = System.Drawing.Color.Empty;
			this.borderSetter.Location = new System.Drawing.Point(375, 206);
			this.borderSetter.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.borderSetter.MixBorders = unvell.ReoGrid.BorderPositions.None;
			this.borderSetter.Name = "borderSetter";
			this.borderSetter.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.borderSetter.Rows = 2;
			this.borderSetter.Size = new System.Drawing.Size(270, 166);
			this.borderSetter.TabIndex = 2;
			this.borderSetter.Text = "borderSetterControl1";
			// 
			// btnBackslash
			// 
			this.btnBackslash.Image = global::unvell.ReoGrid.Editor.Properties.Resources.slash_left_solid;
			this.btnBackslash.Location = new System.Drawing.Point(662, 383);
			this.btnBackslash.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnBackslash.Name = "btnBackslash";
			this.btnBackslash.Size = new System.Drawing.Size(39, 37);
			this.btnBackslash.TabIndex = 14;
			this.btnBackslash.UseVisualStyleBackColor = true;
			this.btnBackslash.Click += new System.EventHandler(this.btnBackslash_Click);
			this.btnBackslash.Visible = false;
			this.btnBackslash.Enabled = false;
			// 
			// btnRight
			// 
			this.btnRight.Image = global::unvell.ReoGrid.Editor.Properties.Resources.right_line_solid;
			this.btnRight.Location = new System.Drawing.Point(606, 383);
			this.btnRight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnRight.Name = "btnRight";
			this.btnRight.Size = new System.Drawing.Size(39, 37);
			this.btnRight.TabIndex = 13;
			this.btnRight.UseVisualStyleBackColor = true;
			this.btnRight.Click += new System.EventHandler(this.btnRight_Click);
			// 
			// btnCenter
			// 
			this.btnCenter.Image = global::unvell.ReoGrid.Editor.Properties.Resources.middle_line_solid;
			this.btnCenter.Location = new System.Drawing.Point(492, 383);
			this.btnCenter.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnCenter.Name = "btnCenter";
			this.btnCenter.Size = new System.Drawing.Size(39, 37);
			this.btnCenter.TabIndex = 12;
			this.btnCenter.UseVisualStyleBackColor = true;
			this.btnCenter.Click += new System.EventHandler(this.btnCenter_Click);
			// 
			// btnLeft
			// 
			this.btnLeft.Image = global::unvell.ReoGrid.Editor.Properties.Resources.left_line_solid;
			this.btnLeft.Location = new System.Drawing.Point(375, 383);
			this.btnLeft.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnLeft.Name = "btnLeft";
			this.btnLeft.Size = new System.Drawing.Size(39, 37);
			this.btnLeft.TabIndex = 11;
			this.btnLeft.UseVisualStyleBackColor = true;
			this.btnLeft.Click += new System.EventHandler(this.btnLeft_Click);
			// 
			// btnSlash
			// 
			this.btnSlash.Image = global::unvell.ReoGrid.Editor.Properties.Resources.slash_right_solid;
			this.btnSlash.Location = new System.Drawing.Point(318, 383);
			this.btnSlash.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnSlash.Name = "btnSlash";
			this.btnSlash.Size = new System.Drawing.Size(39, 37);
			this.btnSlash.TabIndex = 10;
			this.btnSlash.UseVisualStyleBackColor = true;
			this.btnSlash.Click += new System.EventHandler(this.btnSlash_Click);
			this.btnSlash.Visible = false;
			this.btnSlash.Enabled = false;
			// 
			// btnBottom
			// 
			this.btnBottom.Image = global::unvell.ReoGrid.Editor.Properties.Resources.bottom_line_solid;
			this.btnBottom.Location = new System.Drawing.Point(318, 323);
			this.btnBottom.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnBottom.Name = "btnBottom";
			this.btnBottom.Size = new System.Drawing.Size(39, 37);
			this.btnBottom.TabIndex = 9;
			this.btnBottom.UseVisualStyleBackColor = true;
			this.btnBottom.Click += new System.EventHandler(this.btnBottom_Click);
			// 
			// btnMiddle
			// 
			this.btnMiddle.Image = global::unvell.ReoGrid.Editor.Properties.Resources.center_line_solid;
			this.btnMiddle.Location = new System.Drawing.Point(318, 265);
			this.btnMiddle.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnMiddle.Name = "btnMiddle";
			this.btnMiddle.Size = new System.Drawing.Size(39, 37);
			this.btnMiddle.TabIndex = 8;
			this.btnMiddle.UseVisualStyleBackColor = true;
			this.btnMiddle.Click += new System.EventHandler(this.btnMiddle_Click);
			// 
			// btnTop
			// 
			this.btnTop.Image = global::unvell.ReoGrid.Editor.Properties.Resources.top_line_solid;
			this.btnTop.Location = new System.Drawing.Point(318, 206);
			this.btnTop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnTop.Name = "btnTop";
			this.btnTop.Size = new System.Drawing.Size(39, 37);
			this.btnTop.TabIndex = 7;
			this.btnTop.UseVisualStyleBackColor = true;
			this.btnTop.Click += new System.EventHandler(this.btnTop_Click);
			// 
			// btnInside
			// 
			this.btnInside.Image = global::unvell.ReoGrid.Editor.Properties.Resources.inside_solid_32;
			this.btnInside.Location = new System.Drawing.Point(212, 42);
			this.btnInside.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnInside.Name = "btnInside";
			this.btnInside.Size = new System.Drawing.Size(63, 62);
			this.btnInside.TabIndex = 6;
			this.btnInside.UseVisualStyleBackColor = true;
			this.btnInside.Click += new System.EventHandler(this.btnInside_Click);
			// 
			// btnOutline
			// 
			this.btnOutline.Image = global::unvell.ReoGrid.Editor.Properties.Resources.outline_solid_32;
			this.btnOutline.Location = new System.Drawing.Point(120, 42);
			this.btnOutline.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnOutline.Name = "btnOutline";
			this.btnOutline.Size = new System.Drawing.Size(68, 62);
			this.btnOutline.TabIndex = 5;
			this.btnOutline.UseVisualStyleBackColor = true;
			this.btnOutline.Click += new System.EventHandler(this.btnOutline_Click);
			// 
			// btnNone
			// 
			this.btnNone.Image = global::unvell.ReoGrid.Editor.Properties.Resources.none_border_32;
			this.btnNone.Location = new System.Drawing.Point(27, 42);
			this.btnNone.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnNone.Name = "btnNone";
			this.btnNone.Size = new System.Drawing.Size(68, 62);
			this.btnNone.TabIndex = 4;
			this.btnNone.UseVisualStyleBackColor = true;
			this.btnNone.Click += new System.EventHandler(this.btnNone_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.btnNone);
			this.groupBox1.Controls.Add(this.btnOutline);
			this.groupBox1.Controls.Add(this.btnInside);
			this.groupBox1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.groupBox1.Location = new System.Drawing.Point(304, 20);
			this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.groupBox1.Size = new System.Drawing.Size(423, 134);
			this.groupBox1.TabIndex = 15;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Preset Styles";
			// 
			// groupBox2
			// 
			this.groupBox2.Location = new System.Drawing.Point(304, 177);
			this.groupBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.groupBox2.Size = new System.Drawing.Size(423, 265);
			this.groupBox2.TabIndex = 16;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Borders";
			// 
			// BorderPropertyPage
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.btnBackslash);
			this.Controls.Add(this.btnRight);
			this.Controls.Add(this.btnCenter);
			this.Controls.Add(this.btnLeft);
			this.Controls.Add(this.btnSlash);
			this.Controls.Add(this.btnBottom);
			this.Controls.Add(this.btnMiddle);
			this.Controls.Add(this.btnTop);
			this.Controls.Add(this.borderSetter);
			this.Controls.Add(this.grpLine);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.groupBox2);
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.Name = "BorderPropertyPage";
			this.Size = new System.Drawing.Size(854, 563);
			this.grpLine.ResumeLayout(false);
			this.grpLine.PerformLayout();
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private BorderStyleListControl borderStyleList;
		private System.Windows.Forms.GroupBox grpLine;
		private ColorComboBox borderColorSelector;
		private System.Windows.Forms.Label labColor;
		private System.Windows.Forms.Label labStyle;
		private BorderSetterControl borderSetter;
		private System.Windows.Forms.Button btnNone;
		private System.Windows.Forms.Button btnOutline;
		private System.Windows.Forms.Button btnInside;
		private System.Windows.Forms.Button btnTop;
		private System.Windows.Forms.Button btnMiddle;
		private System.Windows.Forms.Button btnBottom;
		private System.Windows.Forms.Button btnSlash;
		private System.Windows.Forms.Button btnLeft;
		private System.Windows.Forms.Button btnCenter;
		private System.Windows.Forms.Button btnRight;
		private System.Windows.Forms.Button btnBackslash;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
	}
}
