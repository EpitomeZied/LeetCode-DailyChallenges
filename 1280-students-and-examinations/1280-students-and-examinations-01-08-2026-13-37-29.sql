select Students.student_id, Students.student_name, Subjects.subject_name, COUNT(Examinations.subject_name) AS 'attended_exams'
from Students
         CROSS JOIN Subjects
         LEFT JOIN Examinations ON Students.student_id = Examinations.student_id
                                    AND Subjects.subject_name = Examinations.subject_name
GROUP BY Students.student_id, student_name, subject_name
ORDER BY  student_id , subject_name;