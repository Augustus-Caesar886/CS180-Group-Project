from sentence_transformers import SentenceTransformer, util
import sys

model = SentenceTransformer('all-MiniLM-L6-v2')

majors = {
    "Computer Science": "Designing algorithms, developing software, and solving computational problems.",
    "Mechanical Engineering": "Designing machines, engines, and solving physical systems problems.",
    "Electrical Engineering": "Designing circuits, hardware, electrical tools, machines, and solving electrical systems problems",
    "Civil Engineering": "Designing cities, infrastructure, buildings, and solving urban planning problems",
    "Chemical Engineering": "Designing chemical agents, testing products, and solving chemical problems"
}

major_names = list(majors.keys())
descriptions = list(majors.values())
description_embeddings = model.encode(descriptions, convert_to_tensor=True)

if len(sys.argv) > 1:
    response = ' '.join(sys.argv[1:])
else:
    response = "I enjoy writing persuasive essays, reading about social structures, and analyzing current events." #sample

response_embedding = model.encode(response, convert_to_tensor=True)

cos_scores = util.cos_sim(response_embedding, description_embeddings)[0]
best_match_idx = cos_scores.argmax()
predicted_major = major_names[best_match_idx]
print("Predicted major:", predicted_major)