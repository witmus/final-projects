using Microsoft.EntityFrameworkCore.Migrations;

namespace IOWpf.Migrations
{
    public partial class AddBillPhotoPath : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "bill_photo_path",
                table: "Expenses",
                nullable: true);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "bill_photo_path",
                table: "Expenses");
        }
    }
}
