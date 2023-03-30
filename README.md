
# Library Management Tool - Công cụ quản lí thư viện

---

## Project description - Mô tả dự án

Đây là đồ án kết thúc môn học **Cấu trúc dữ liệu và Giải thuật** do thầy ***Lưu Nguyễn Kì Thư*** phụ trách.

***Sinh viên thực hiện:***

| Họ và tên | MSSV |
| :--- | :--- |
| Nguyễn Nhật Minh | N21DCCN053 |
| Trần Thị Thùy Ngân | N21DCCN055 |
| Nguyễn Ngọc Thiên Phúc | N21DCCN066 |

### Chi tiết đề bài

Thiết kế một chương trình thư viện có các danh sách sau:

1. **Đầu sách**: là một danh sách tuyến tính theo dạng mảng con trỏ. Mỗi phần tử của danh sách là một đầu sách có các `field` sau:

    | Fields | Description | Data type |
    | ---: | :--- | :--- |
    | <ins>***ISBN***</ins> | Mã đầu sách | Chuỗi duy nhất tối đa $4$ kí tự gồm các chữ cái in hoa từ `A` - `Z` |
    | Tên sách | Tên của đầu sách | Chuỗi tối đa $50$ kí tự |
    | Số trang | Số trang của đầu sách | Số nguyên dương |
    | Tác giả | Tên tác giả đầu sách | Chuỗi tối đa $50$ kí tự |
    | Năm xuất bản | Năm xuất bản đầu sách | Số nguyên dương |
    | Thể loại | Thể loại của đầu sách | Chuỗi tối đa $30$ kí tự |
    | Con trỏ danh mục sách | Con trỏ trỏ đến danh sách các sách thuộc đầu sách | Con trỏ |

    ***Ghi chú:*** 
    1. Danh sách đầu sách luôn tăng dần theo tên sách.
    2. Chuỗi `ISBN` duy nhất cho mỗi đầu sách.

2. **Danh mục sách**: là một danh sách liên kết đơn với mỗi `node` là một sách có các `field` sau:

    | Fields | Description | Data type |
    | ---: | :--- | :--- |
    | <ins>***Mã sách***</ins> | Mã sách của từng cuốn sách thuộc đầu sách | Chuỗi duy nhất tối đa $14$ kí tự |
    | Trạng thái | Trạng thái của cuốn sách hiện tại | Enum |
    | Vị trí | Mô tả vị trí của cuốn sách trên giá sách | Chuỗi định dạng sẵn |

    - Mỗi cuốn sách thuộc đầu sách có các trạng thái như sau:

        | Trạng thái | Ý nghĩa |
        | :---: | :--- |
        | 0 | Cho mượn được |
        | 1 | Đã có độc giả mượn (không mượn được) |
        | 2 | Đã thanh lý (không mượn được) |

    - Vị trí của sách sẽ gồm các thông tin vị trí dòng, cột và tủ. Theo đó chuỗi vị trí sẽ có định dạng: `DONG {X} COT {Y} TU {Z}` và có tối đa $20$ kí tự.

    ***Ghi chú:*** Mã sách duy nhất cho mỗi cuốn sách.

3. **Danh sách thẻ độc giả**: là cây nhị phân tìm kiếm cân bằng với mỗi `node` có các `field` sau:

    | Fields | Description | Data type |
    | ---: | :--- | :--- |
    | <ins>***Mã thẻ***</ins> | Mã thẻ của mỗi độc giả | Số nguyên ngẫu nhiên phân biệt sinh tự động |
    | Họ | Họ của độc giả | Chuỗi tối đa $30$ kí tự |
    | Tên | Tên của độc giả | Chuỗi tối đa $10$ kí tự |
    | Phái | Giới tính của độc giả | Enum |
    | Trạng thái của thẻ | Mô tả trạng thái hoạt động của thẻ | Enum |
    | Con trỏ | Trỏ tới danh sách các cuốn sách đang được mượn | Con trỏ |

    - Mỗi thẻ độc giả có các trạng thái sau:

        | Trạng thái | Ý nghĩa |
        | :---: | :--- |
        | 0 | Thẻ bị khóa (không mượn được sách) |
        | 1 | Thẻ đang hoạt động (được mượn sách) |

    ***Ghi chú:*** Mã thẻ được sinh tự động ngẫu nhiên.

4. **Danh sách mượn trả**: là danh sách liên kết kép với mỗi `node` có các field sau:

    | Fields | Description | Data type |
    | ---: | :--- | :--- |
    | <ins>***Mã sách***</ins> | Mã của cuốn sách đang mượn | Chuỗi tối đa $14$ ksi tự |
    | <ins>***Ngày mượn***</ins> | Ngày mượn cuốn sách | Date & Time |
    | Ngày trả | Ngày trả sách | Date & Time |
    | Trạng thái | Trạng thái của cuốn sách đang mượn | Enum |

    - Mỗi cuốn sách sẽ có các trạng thái sau:

        | Trạng thái | Ý nghĩa |
        | :---: | :--- |
        | 0 | Sách đang mượn (chưa trả) |
        | 1 | Sách đã trả |
        | 2 | Sách bị mất |

### Yêu cầu đề bài

1. Nhập thẻ độc giả: thêm / xóa / hiệu chỉnh thông tin thẻ độc giả. Mã thẻ độc giả được chương trình tự động lấy ngẫu nhiên và không trùng với các mã thẻ độc giả cũ; Phái chỉ nhận ‘Nam’ hoặc ‘Nữ’; trạng thái thẻ = 0 khi thẻ bị khóa, trạng thái thẻ = 1 khi thẻ đang hoạt động (được quyền mượn sách).

2. In danh sách độc giả: in ra màn hình theo thứ tự tên+họ tăng dần hoặc theo thứ tự mã độc giả tăng dần theo yêu cầu của thủ thư.

3. Nhập thông tin đầu sách và đánh mã sách tự động. Chương trình cho phép xóa 1 mã sách nếu mã sách này chưa cho độc giả mượn.

**4. In danh sách các đầu sách trong thư viện theo từng thể loại, trong từng thể loại thì in theo thứ tự tên sách tăng dần.

5. Tìm thông tin sách dựa vào tên sách: in ra các thông tin mã ISBN, tên sách, tác giả, năm xuất bản, thể loại, các mã sách , trạng thái mã sách trong thư viện.
**
6. Mượn sách: nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, không cho mượn khi giữ 1 sách quá hạn (7 ngày) hoặc nếu các sách mượn thuộc cùng 1 đầu sách.

7. Trả sách.

8. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn.

9. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần. Kết xuất:
    
    `Mathe | Ho | tên | Masach |Tên sách | Ngày mượn | Số ngày quá hạn`

10. In 10 đầu sách có số lượt mượn nhiều nhất.

---
