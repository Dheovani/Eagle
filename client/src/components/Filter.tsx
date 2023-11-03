import { useEffect, useState } from "react";
import { GiBroom } from "react-icons/gi";
import { GetMethod } from "../utils/RestMethods";
import { Tooltip } from "../utils/Tooltip";
import { FILTER, History } from "./History";

export interface Filter {
	filter: string;
	id?: number;
	date?: Date;
}

export const FilterInput = (props: any): JSX.Element => {
	const [selected, setSelected] = useState(false);
	const [filter, setFilter] = useState<Filter[]>([]);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Filter", (status: number, response: any) => {
			if (status === 200) setFilter(response);
		});
	};

	useEffect(() => {
		updateHistory();
	}, [selected]);

	const renderHistory = (): JSX.Element => {
		if (!filter?.length) return <div></div>;

		return (
			<History
				items={filter}
				endpoint={FILTER}
				updateDefaultValue={props.updateDefaultValue}
			/>
		);
	};

	const info =
		"Este campo contém as extensões de arquivos aceitas na pesquisa. " +
		'Para selecionar múltiplas extensões, utilize ";".';

	return (
		<>
			<h2>
				Filtros / Extensões
				{<Tooltip info={info} />}
			</h2>
			<div className="input-content">
				<input
					className="fields"
					type="text"
					name="filter"
					id="filter"
					value={props.defaultValue}
					placeholder={selected ? "" : "Exemplo: .js; .jsx;"}
					disabled={props.disable}
					onFocus={() => setSelected(true)}
					onBlur={() => setSelected(false)}
					onChange={(e) => {
						const filter = {
							filter: e.target.value,
							date: new Date(),
						};
						props.updateDefaultValue(filter);
					}}
				/>
				
				<button
					disabled={props.disable}
					className="input-buttons"
					onClick={() => props.updateDefaultValue({ filter: "" })}>
					<GiBroom />
				</button>

				<label htmlFor="ignoreCase">Considerar capitalização</label>
				<input
					className="checkbox"
					type="checkbox"
					checked={props.checked}
					disabled={props.disable}
					onChange={() => {
						props.setIgnoreCase(!props.checked);
					}}
					name="ignoreCase"
					id="ignoreCase"
				/>
			</div>

			{selected && renderHistory()}
		</>
	);
};
