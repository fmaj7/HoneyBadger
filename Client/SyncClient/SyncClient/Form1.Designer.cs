﻿namespace SyncClient
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.lbl_location = new System.Windows.Forms.Label();
            this.txt_location = new System.Windows.Forms.TextBox();
            this.btn_move = new System.Windows.Forms.Button();
            this.txt_changes = new System.Windows.Forms.TextBox();
            this.btn_clear = new System.Windows.Forms.Button();
            this.gpb_server = new System.Windows.Forms.GroupBox();
            this.btn_connect = new System.Windows.Forms.Button();
            this.txt_port = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_ip = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_sendmsg = new System.Windows.Forms.Button();
            this.gpb_server.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbl_location
            // 
            this.lbl_location.AutoSize = true;
            this.lbl_location.Location = new System.Drawing.Point(23, 11);
            this.lbl_location.Name = "lbl_location";
            this.lbl_location.Size = new System.Drawing.Size(83, 12);
            this.lbl_location.TabIndex = 0;
            this.lbl_location.Text = "Sync location";
            // 
            // txt_location
            // 
            this.txt_location.Location = new System.Drawing.Point(37, 30);
            this.txt_location.Name = "txt_location";
            this.txt_location.Size = new System.Drawing.Size(241, 21);
            this.txt_location.TabIndex = 1;
            this.txt_location.Text = "C:\\Users\\Samlou\\Dropbox";
            // 
            // btn_move
            // 
            this.btn_move.Location = new System.Drawing.Point(297, 30);
            this.btn_move.Name = "btn_move";
            this.btn_move.Size = new System.Drawing.Size(75, 23);
            this.btn_move.TabIndex = 2;
            this.btn_move.Text = "move...";
            this.btn_move.UseVisualStyleBackColor = true;
            this.btn_move.Click += new System.EventHandler(this.btn_move_Click);
            // 
            // txt_changes
            // 
            this.txt_changes.Location = new System.Drawing.Point(12, 159);
            this.txt_changes.Multiline = true;
            this.txt_changes.Name = "txt_changes";
            this.txt_changes.Size = new System.Drawing.Size(343, 332);
            this.txt_changes.TabIndex = 3;
            // 
            // btn_clear
            // 
            this.btn_clear.Location = new System.Drawing.Point(361, 195);
            this.btn_clear.Name = "btn_clear";
            this.btn_clear.Size = new System.Drawing.Size(75, 23);
            this.btn_clear.TabIndex = 4;
            this.btn_clear.Text = "clear";
            this.btn_clear.UseVisualStyleBackColor = true;
            this.btn_clear.Click += new System.EventHandler(this.btn_clear_Click);
            // 
            // gpb_server
            // 
            this.gpb_server.Controls.Add(this.btn_connect);
            this.gpb_server.Controls.Add(this.txt_port);
            this.gpb_server.Controls.Add(this.label2);
            this.gpb_server.Controls.Add(this.txt_ip);
            this.gpb_server.Controls.Add(this.label1);
            this.gpb_server.Location = new System.Drawing.Point(12, 78);
            this.gpb_server.Name = "gpb_server";
            this.gpb_server.Size = new System.Drawing.Size(444, 56);
            this.gpb_server.TabIndex = 6;
            this.gpb_server.TabStop = false;
            this.gpb_server.Text = "Server";
            // 
            // btn_connect
            // 
            this.btn_connect.Location = new System.Drawing.Point(349, 17);
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.Size = new System.Drawing.Size(75, 23);
            this.btn_connect.TabIndex = 4;
            this.btn_connect.Text = "connect";
            this.btn_connect.UseVisualStyleBackColor = true;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // txt_port
            // 
            this.txt_port.Location = new System.Drawing.Point(256, 15);
            this.txt_port.Name = "txt_port";
            this.txt_port.Size = new System.Drawing.Size(64, 21);
            this.txt_port.TabIndex = 3;
            this.txt_port.Text = "3432";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(214, 18);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Port:";
            // 
            // txt_ip
            // 
            this.txt_ip.Location = new System.Drawing.Point(48, 14);
            this.txt_ip.Name = "txt_ip";
            this.txt_ip.Size = new System.Drawing.Size(142, 21);
            this.txt_ip.TabIndex = 1;
            this.txt_ip.Text = "127.0.0.1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP:";
            // 
            // btn_sendmsg
            // 
            this.btn_sendmsg.Location = new System.Drawing.Point(361, 250);
            this.btn_sendmsg.Name = "btn_sendmsg";
            this.btn_sendmsg.Size = new System.Drawing.Size(75, 23);
            this.btn_sendmsg.TabIndex = 7;
            this.btn_sendmsg.Text = "sendMsg";
            this.btn_sendmsg.UseVisualStyleBackColor = true;
            this.btn_sendmsg.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(468, 506);
            this.Controls.Add(this.btn_sendmsg);
            this.Controls.Add(this.gpb_server);
            this.Controls.Add(this.btn_clear);
            this.Controls.Add(this.txt_changes);
            this.Controls.Add(this.btn_move);
            this.Controls.Add(this.txt_location);
            this.Controls.Add(this.lbl_location);
            this.Name = "Form1";
            this.Text = "Preferences";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.gpb_server.ResumeLayout(false);
            this.gpb_server.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbl_location;
        private System.Windows.Forms.TextBox txt_location;
        private System.Windows.Forms.Button btn_move;
        private System.Windows.Forms.TextBox txt_changes;
        private System.Windows.Forms.Button btn_clear;
        private System.Windows.Forms.GroupBox gpb_server;
        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.TextBox txt_port;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_ip;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_sendmsg;
    }
}
